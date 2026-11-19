// Data registration is stable even when the game's loader rewrites code.
export async function locateGameModule(api){
  const {Process,Memory,log}=api;
  if(Process.arch!=='arm64')throw Error('Требуется ARM64');
  const expected=[[0,0x5fae],[16,0x3c16],[32,0x1548e],[48,0x10e59],[64,0x1db5d],[80,0x5d05],[96,0x5d05]];
  const pattern=expected.map(([offset,value],index)=>{
    const bytes=Array.from({length:8},(_,byte)=>Math.floor(value/2**(8*byte))&255).map(byte=>byte.toString(16).padStart(2,'0')).join(' ');
    return bytes+(index<expected.length-1?' ?? ?? ?? ?? ?? ?? ?? ??':'');
  }).join(' ');
  const unique=new Map();
  for(const protection of ['r--','rw-','rwx'])for(const range of Process.enumerateRanges({protection,coalesce:false}))unique.set(range.base.toString(),range);
  const ranges=[...unique.values()]
    .filter(range=>range.size>=0x10000&&!/^(\/system|\/apex|\/vendor|\/product)\//.test(range.file?String(range.file.path):''))
    .sort((a,b)=>{
      const priority=range=>range.protection==='r-x'?2:range.size>=0x100000&&range.size<=0x1000000?0:1;
      return priority(a)-priority(b)||a.size-b.size;
    });
  const scan=(base,size)=>new Promise(resolve=>{
    const hits=[];
    try{Memory.scan(base,size,pattern,{onMatch(address){hits.push(address);if(hits.length>=8)return 'stop';},onError(){resolve(hits);},onComplete(){resolve(hits);}});}
    catch(error){resolve(hits);}
  });
  let bytes=0;
  for(const range of ranges)for(let offset=0;offset<range.size;offset+=0x100000){
    const size=Math.min(0x100000+104,range.size-offset);
    const hits=await scan(range.base.add(offset),size);bytes+=size;
    for(const address of hits)try{
      if(!expected.every(([offset,value])=>address.add(offset).readU64().toNumber()===value))continue;
      const base=address.sub(0xae4fe48),code=base.add(0x6402be0),mapped=Process.findRangeByAddress(code);
      if(mapped&&mapped.protection.includes('x')){log('CLOUD:base-found-data '+base+' code='+code+' scanBytes='+bytes);return base;}
    }catch(error){}
  }
  log('CLOUD:base-not-found ranges='+ranges.length+' scanBytes='+bytes);return null;
}
