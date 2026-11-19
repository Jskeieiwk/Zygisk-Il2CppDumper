export function createSceneEffects(context){
  const {native,settings}=context,colorType=['float','float','float','float'];
  const getFog=native(0xa7458ec,'bool',['pointer']),setFog=native(0xa745a64,'void',['bool','pointer']);
  const getEnd=native(0xa745d48,'float',['pointer']),setEnd=native(0xa745eb0,'void',['float','pointer']);
  const getColor=native(0xa74603c,colorType,['pointer']),setColor=native(0xa7461e0,'void',[colorType,'pointer']);
  let original=null,previous='';
  function rgba(value){return [1,3,5].map(index=>parseInt(value.slice(index,index+2),16)/255).concat(1);}
  function reset(){
    const saved=original;original=null;previous='';
    if(!saved||saved.scene!==context.scene())return;
    setFog(saved.fog?1:0,ptr(0));setEnd(saved.end,ptr(0));setColor(saved.color,ptr(0));
  }
  function update(){
    if(!settings.Fog||!context.canRun()){reset();return;}
    const scene=context.scene();
    if(original&&original.scene!==scene){original=null;previous='';}
    if(!original)original={scene,fog:getFog(ptr(0)),end:getEnd(ptr(0)),color:getColor(ptr(0))};
    const key=settings['Fog Distance']+settings['Fog Color'];if(previous===key)return;
    setFog(1,ptr(0));setEnd(settings['Fog Distance'],ptr(0));setColor(rgba(settings['Fog Color']),ptr(0));previous=key;
  }
  return {update,reset};
}
