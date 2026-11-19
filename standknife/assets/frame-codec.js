// Packs batched overlay primitives into integers before they cross to Java.
// JSON.stringify of long doubles was the largest single cost of an overlay frame under QuickJS (about 60 percent);
// integers take the fast path and shrink the string about 3.5 times. Positions keep 1/4 pixel, sizes 1/8 pixel.
// CanvasBatch.POS and CanvasBatch.SIZE must stay equal to these scales.
export const POS_SCALE=4,SIZE_SCALE=8;
// Input primitives (see CanvasBatch.drawPacked for the packed layouts):
//   [1,[x1,y1,x2,y2,...],strokeWidth,color]   lines
//   [2,text,x,y,textSize,color]               text
//   [3,left,top,right,bottom,color]           filled rectangle
//   [4,x,y,radius,strokeWidth,color]          stroked circle
//   [5,avatarId,left,top,side]                avatar registered with CanvasBatch.setAvatar
// Output: JSON string. A primitive with a non-finite number is dropped instead of poisoning the whole frame.
export function encodeFrame(commands){
  const out=[];
  for(let i=0;i<commands.length;i++){
    const command=commands[i],kind=command[0];
    if(kind===1){
      const points=command[1],width=Math.round(command[2]*SIZE_SCALE),packed=new Array(points.length);
      let valid=Number.isFinite(width);
      for(let j=0;j<points.length;j++){
        const value=Math.round(points[j]*POS_SCALE);
        if(!Number.isFinite(value)){valid=false;break;}
        packed[j]=value;
      }
      if(valid)out.push([1,packed,width,command[3]|0]);
    }else if(kind===2){
      const x=Math.round(command[2]*POS_SCALE),y=Math.round(command[3]*POS_SCALE),size=Math.round(command[4]*SIZE_SCALE);
      if(Number.isFinite(x)&&Number.isFinite(y)&&Number.isFinite(size))out.push([2,String(command[1]),x,y,size,command[5]|0]);
    }else if(kind===3){
      const l=Math.round(command[1]*POS_SCALE),t=Math.round(command[2]*POS_SCALE),r=Math.round(command[3]*POS_SCALE),b=Math.round(command[4]*POS_SCALE);
      if(Number.isFinite(l)&&Number.isFinite(t)&&Number.isFinite(r)&&Number.isFinite(b))out.push([3,l,t,r,b,command[5]|0]);
    }else if(kind===4){
      const x=Math.round(command[1]*POS_SCALE),y=Math.round(command[2]*POS_SCALE),radius=Math.round(command[3]*POS_SCALE),width=Math.round(command[4]*SIZE_SCALE);
      if(Number.isFinite(x)&&Number.isFinite(y)&&Number.isFinite(radius)&&Number.isFinite(width))out.push([4,x,y,radius,width,command[5]|0]);
    }else if(kind===5){
      const left=Math.round(command[2]*POS_SCALE),top=Math.round(command[3]*POS_SCALE),side=Math.round(command[4]*POS_SCALE);
      if(Number.isInteger(command[1])&&Number.isFinite(left)&&Number.isFinite(top)&&Number.isFinite(side))out.push([5,command[1],left,top,side]);
    }
  }
  return JSON.stringify(out);
}
