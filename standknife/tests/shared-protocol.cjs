// JS writer -> Java reader, end to end: the real shared-frame.js packs a frame into a byte image of the shared buffer, the real
// CanvasBatch reads that image at a vsync and draws it, and the geometry Java publishes is read back by the real JS code.
// This is the test that catches a layout disagreement between the two languages.
const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm'),os=require('node:os'),path=require('node:path');
const {FakeAddress}=require('./helpers/fake-memory.cjs');
const {runJava}=require('./helpers/android-stubs.cjs');
let clock=1700000000000;
const context=vm.createContext({Date:{now:()=>clock},Int32Array,Number,Math,String,ArrayBuffer});
vm.runInContext(fs.readFileSync('assets/shared-frame.js','utf8').replaceAll('export const','const').replaceAll('export function','function')+
 '\nglobalThis.api={createSharedFrame,HEADER_WORDS,CAPACITY_WORDS};',context);
const {createSharedFrame,HEADER_WORDS,CAPACITY_WORDS}=context.api;

const text='He said "hi", \\ 名前 \u{1F600}';
const commands=[[1,[1,2,3.5,4.25],2,-1],[2,text,10,20,13,-16777216],[3,1,2,10,20,-1],[4,10,20,5,2,3],[5,1,2,4,25]];
const memory=Buffer.alloc(CAPACITY_WORDS*4);
const shared=createSharedFrame({address:new FakeAddress(memory),now:()=>clock});
const words=shared.pack(commands);shared.commit(words);

const dir=fs.mkdtempSync(path.join(os.tmpdir(),'cloud-protocol-'));
const input=path.join(dir,'frame.bin'),output=path.join(dir,'header.bin');
fs.writeFileSync(input,memory.subarray(0,(HEADER_WORDS+words)*4));
const javaSource=`package dev.cloud.standknife;
import android.graphics.*;import android.content.Context;import android.os.SystemClock;import android.view.View;
import java.nio.*;import java.nio.file.*;
public class ProtocolCheck {
  public static void main(String[] args)throws Exception{
    byte[] image=Files.readAllBytes(Paths.get(args[0]));
    CanvasBatch view=new CanvasBatch(new Context());view.width=300;view.height=200;view.locX=10;view.locY=20;
    View game=new View(new Context());game.width=150;game.height=80;game.locX=15;game.locY=27;view.setGameSurface(game);
    view.setAvatar(1,new byte[]{64,32},0,0,0,0);
    ByteBuffer shared=view.sharedBuffer();
    ByteBuffer copy=shared.duplicate().order(shared.order());copy.position(0);copy.put(image);
    SystemClock.now=1000;
    view.step();
    Canvas canvas=new Canvas();view.onDraw(canvas);
    StringBuilder escaped=new StringBuilder();
    for(char c:canvas.ops.toCharArray()){if(c>126)escaped.append(String.format("\\\\u%04x",(int)c));else escaped.append(c);}
    System.out.println(escaped);
    byte[] header=new byte[CanvasBatch.HEADER_WORDS*4];ByteBuffer view2=shared.duplicate();view2.position(0);view2.get(header);
    Files.write(Paths.get(args[1]),header);
  }
}`;
let stdout,header;
try{
  stdout=runJava({'dev/cloud/standknife/ProtocolCheck.java':javaSource},'dev.cloud.standknife.ProtocolCheck',[input,output]);
  header=fs.readFileSync(output);
}finally{fs.rmSync(dir,{recursive:true,force:true});}

const escape=value=>[...value].map(character=>{
  // Java prints UTF-16 code units, so astral characters appear as two escapes.
  return [...character].map(()=>'').length&&character.codePointAt(0)>0xffff
    ?'\\u'+character.charCodeAt(0).toString(16).padStart(4,'0')+'\\u'+character.charCodeAt(1).toString(16).padStart(4,'0')
    :character.charCodeAt(0)>126?'\\u'+character.charCodeAt(0).toString(16).padStart(4,'0'):character;
}).join('');
const expected='save;translate(5.0,7.0);clip(0.0,0.0,150.0,80.0);lines[1.0, 2.0, 3.5, 4.25]w2.0c-1;'+
  'text('+escape(text)+',10.0,20.0,size13.0,c-16777216);rect(1.0,2.0,10.0,20.0,c-1);circle(10.0,20.0,5.0,w2.0,c3);'+
  'bitmap(64x32,null,F(2.0,4.0,27.0,29.0),c-1);restore;';
assert.equal(stdout.trim(),expected,'Java must draw exactly what the script packed');

// Geometry published by Java is parsed by the same JS code the script uses at run time.
const image=Buffer.alloc(CAPACITY_WORDS*4);header.copy(image);
const geometry=createSharedFrame({address:new FakeAddress(image)}).geometry();
assert.deepEqual({...geometry},{width:300,height:200,x:5,y:7,clipWidth:150,clipHeight:80,valid:true});
console.log('Shared-memory protocol: JS-packed frame drawn by Java exactly, and Java geometry read back by JS.');
