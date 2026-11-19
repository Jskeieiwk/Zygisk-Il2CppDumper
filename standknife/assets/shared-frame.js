// Shared-memory frame transport: the script writes packed integers into the direct ByteBuffer owned by CanvasBatch and the
// Java view reads the newest frame on the UI thread at every vsync. No Frida->Java call is made per frame.
// Layout (32-bit words, native byte order) must match CanvasBatch:
//   0 sequence (even; written last)   1 marker = sequence ^ MAGIC (written just before the sequence)   2 payload length
//   3 write time (wall clock, low 31 bits)   8 self-test word   9 display delay in ms (script -> Java)   16..22 Java -> script geometry
//   32.. payload
export const HEADER_WORDS=32,CAPACITY_WORDS=1<<18,MAGIC=0x5EED5EED;
export const W_SEQ=0,W_MARKER=1,W_LENGTH=2,W_STAMP=3,W_SELFTEST=8,W_DELAY=9,W_GEOMETRY=16;
export const POS_SCALE=4,SIZE_SCALE=8,MAX_TEXT=160,LIMIT=1e9;

const scaled=(value,scale)=>{const result=Math.round(value*scale);return Number.isFinite(result)&&result>-LIMIT&&result<LIMIT?result:NaN;};

// Packs primitives into `out` (an Int32Array) and returns the number of words used. Primitives that do not fit, or that contain
// a non-finite or absurd number, are dropped whole. Input and output layouts are documented in assets/frame-codec.js and CanvasBatch.
//   [1,[x1,y1,x2,y2,...],strokeWidth,color] -> 1,count,width,color,coords...
//   [2,text,x,y,textSize,color]             -> 2,x,y,size,color,length,chars...
//   [3,left,top,right,bottom,color]         -> 3,l,t,r,b,color
//   [4,x,y,radius,strokeWidth,color]        -> 4,x,y,r,width,color
//   [5,avatarId,left,top,side]              -> 5,id,left,top,side
export function packFrame(commands,out,limit=out.length){
  let n=0;
  for(let i=0;i<commands.length;i++){
    const command=commands[i],kind=command[0],start=n;
    let ok=true;
    if(kind===1){
      const points=command[1],count=points.length,width=scaled(command[2],SIZE_SCALE);
      if(!Number.isFinite(width)||n+4+count>limit)continue;
      out[n++]=1;out[n++]=count;out[n++]=width;out[n++]=command[3]|0;
      for(let j=0;j<count;j++){const value=scaled(points[j],POS_SCALE);if(Number.isNaN(value)){ok=false;break;}out[n++]=value;}
    }else if(kind===2){
      const string=String(command[1]),length=Math.min(string.length,MAX_TEXT);
      const x=scaled(command[2],POS_SCALE),y=scaled(command[3],POS_SCALE),size=scaled(command[4],SIZE_SCALE);
      if(Number.isNaN(x)||Number.isNaN(y)||Number.isNaN(size)||n+6+length>limit)continue;
      out[n++]=2;out[n++]=x;out[n++]=y;out[n++]=size;out[n++]=command[5]|0;out[n++]=length;
      for(let j=0;j<length;j++)out[n++]=string.charCodeAt(j);
    }else if(kind===3){
      const l=scaled(command[1],POS_SCALE),t=scaled(command[2],POS_SCALE),r=scaled(command[3],POS_SCALE),b=scaled(command[4],POS_SCALE);
      if(Number.isNaN(l)||Number.isNaN(t)||Number.isNaN(r)||Number.isNaN(b)||n+6>limit)continue;
      out[n++]=3;out[n++]=l;out[n++]=t;out[n++]=r;out[n++]=b;out[n++]=command[5]|0;
    }else if(kind===4){
      const x=scaled(command[1],POS_SCALE),y=scaled(command[2],POS_SCALE),radius=scaled(command[3],POS_SCALE),width=scaled(command[4],SIZE_SCALE);
      if(Number.isNaN(x)||Number.isNaN(y)||Number.isNaN(radius)||Number.isNaN(width)||n+6>limit)continue;
      out[n++]=4;out[n++]=x;out[n++]=y;out[n++]=radius;out[n++]=width;out[n++]=command[5]|0;
    }else if(kind===5){
      const left=scaled(command[2],POS_SCALE),top=scaled(command[3],POS_SCALE),side=scaled(command[4],POS_SCALE);
      if(!Number.isInteger(command[1])||Number.isNaN(left)||Number.isNaN(top)||Number.isNaN(side)||n+5>limit)continue;
      out[n++]=5;out[n++]=command[1];out[n++]=left;out[n++]=top;out[n++]=side;
    }else ok=false;
    if(!ok)n=start;
  }
  return n;
}

// address: NativePointer of the direct buffer. Methods only touch memory through add/readS32/writeS32/writeByteArray.
export function createSharedFrame({address,now=Date.now,capacityWords=CAPACITY_WORDS}){
  const out=new Int32Array(capacityWords-HEADER_WORDS),payload=address.add(HEADER_WORDS*4);
  let sequence=0;
  const word=index=>address.add(index*4);
  return {
    // Overlay geometry as the Java view last saw it (updated every vsync): size, game-surface offset and size.
    geometry(){
      return {width:word(W_GEOMETRY).readS32(),height:word(W_GEOMETRY+1).readS32(),x:word(W_GEOMETRY+2).readS32(),y:word(W_GEOMETRY+3).readS32(),
        clipWidth:word(W_GEOMETRY+4).readS32(),clipHeight:word(W_GEOMETRY+5).readS32(),valid:word(W_GEOMETRY+6).readS32()===1};
    },
    pack(commands){return packFrame(commands,out);},
    // Publishes the first `words` packed words: payload first, then the length, the stamp and the display delay (milliseconds
    // Java should hold the frame back to match the game image), then the marker, and the sequence last.
    commit(words,delayMs=0){
      if(words>0)payload.writeByteArray(out.buffer.slice(0,words*4));
      word(W_LENGTH).writeS32(words);
      word(W_STAMP).writeS32(now()&0x7fffffff);
      word(W_DELAY).writeS32(Math.max(0,Math.min(200,Math.round(delayMs)||0)));
      sequence=sequence>=0x7ffffff0?2:sequence+2;
      word(W_MARKER).writeS32((sequence^MAGIC)|0);
      word(W_SEQ).writeS32(sequence);
    },
    word,
    capacityWords
  };
}
