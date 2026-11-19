// Managed objects returned by native calls are raw pointers to Frida. Keep them
// alive while cached; Unity's native lifetime is checked separately via live().
export function createEngine(native) {
  const functions=new Map(),strings=new Map(),types=new Map(),roots=new Map();
  function method(rva,result,args){
    if(!functions.has(rva))functions.set(rva,native(rva,result,args));
    return functions.get(rva);
  }
  function hold(object){
    if(object.isNull())return object;
    const key=object.toString(),entry=roots.get(key);
    if(entry)entry.count++;
    else roots.set(key,{count:1,handle:method(0x9647044,'pointer',['pointer','int','pointer'])(object,2,ptr(0))});
    return object;
  }
  function release(object){
    if(!object||object.isNull())return;
    const key=object.toString(),entry=roots.get(key);
    if(!entry||--entry.count>0)return;
    const storage=Memory.alloc(Process.pointerSize);storage.writePointer(entry.handle);
    method(0x9647058,'void',['pointer','pointer'])(storage,ptr(0));roots.delete(key);
  }
  function string(value){
    if(!strings.has(value)){
      const data=Memory.allocUtf8String(value),length=unescape(encodeURIComponent(value)).length;
      const object=method(0x95103ec,'pointer',['pointer','int','int','pointer'])(data,0,length,ptr(0));
      if(object.isNull())throw Error('Managed string allocation failed');
      strings.set(value,hold(object));
    }
    return strings.get(value);
  }
  function type(name){
    if(!types.has(name)){
      const object=method(0x9823338,'pointer',['pointer','pointer'])(string(name),ptr(0));
      if(object.isNull())throw Error('Missing managed type '+name);
      types.set(name,hold(object));
    }
    return types.get(name);
  }
  function array(object,limit=256){
    if(object.isNull())return [];
    const count=object.add(0x18).readU64().toNumber();
    if(!Number.isSafeInteger(count)||count<0||count>65536)throw Error('Invalid managed array length');
    const result=[];
    for(let index=0;index<Math.min(count,limit);index++)result.push(object.add(0x20+index*8).readPointer());
    return result;
  }
  function find(name,limit=128){
    const objects=method(0xa790358,'pointer',['pointer','pointer'])(type(name),ptr(0));
    if(objects.isNull())return [];
    hold(objects);
    const result=[];
    try{for(const object of array(objects,limit))result.push(hold(object));return result;}
    catch(error){for(const object of result)release(object);throw error;}
    finally{release(objects);}
  }
  function live(object){return !!object&&!object.isNull()&&method(0xa78ebc4,'bool',['pointer','pointer'])(object,ptr(0));}
  function reset(){
    for(const entry of roots.values()){
      const storage=Memory.alloc(Process.pointerSize);storage.writePointer(entry.handle);
      method(0x9647058,'void',['pointer','pointer'])(storage,ptr(0));
    }
    roots.clear();strings.clear();types.clear();
  }
  return {method,hold,release,string,type,array,find,live,reset};
}
