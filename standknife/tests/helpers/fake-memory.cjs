// A fake NativePointer over a Buffer: just the calls shared-frame.js uses. Little-endian, like the device.
class FakeAddress {
  constructor(memory,offset=0,log=null){this.memory=memory;this.offset=offset;this.log=log;}
  add(bytes){return new FakeAddress(this.memory,this.offset+bytes,this.log);}
  readS32(){return this.memory.readInt32LE(this.offset);}
  writeS32(value){if(this.log)this.log.push(['s32',this.offset/4,value|0]);this.memory.writeInt32LE(value|0,this.offset);}
  writeByteArray(bytes){
    const view=Buffer.from(bytes instanceof ArrayBuffer?bytes:new Uint8Array(bytes));
    if(this.log)this.log.push(['bytes',this.offset/4,view.length/4]);
    view.copy(this.memory,this.offset);
  }
}
module.exports={FakeAddress};
