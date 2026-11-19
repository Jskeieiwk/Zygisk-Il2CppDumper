// Unity Matrix4x4 stores columns consecutively. View-space forward is -Z.
// Matrix elements are hoisted into locals and the point is read by index: this runs for every bone of
// every player on every camera frame, and QuickJS array destructuring and closures are slow.
export function createMatrixProjector(view,projection,width,height){
  if(!view||!projection||view.length!==16||projection.length!==16||
    !view.every(Number.isFinite)||!projection.every(Number.isFinite)||width<=0||height<=0)return null;
  const v0=view[0],v1=view[1],v2=view[2],v3=view[3],v4=view[4],v5=view[5],v6=view[6],v7=view[7],
    v8=view[8],v9=view[9],v10=view[10],v11=view[11],v12=view[12],v13=view[13],v14=view[14],v15=view[15];
  const p0=projection[0],p1=projection[1],p3=projection[3],p4=projection[4],p5=projection[5],p7=projection[7],
    p8=projection[8],p9=projection[9],p11=projection[11],p12=projection[12],p13=projection[13],p15=projection[15];
  const halfWidth=width*.5,halfHeight=height*.5;
  return point=>{
    const x=point[0],y=point[1],z=point[2];
    const vx=v0*x+v4*y+v8*z+v12;
    const vy=v1*x+v5*y+v9*z+v13;
    const vz=v2*x+v6*y+v10*z+v14;
    const vw=v3*x+v7*y+v11*z+v15;
    const cx=p0*vx+p4*vy+p8*vz+p12*vw;
    const cy=p1*vx+p5*vy+p9*vz+p13*vw;
    const cw=p3*vx+p7*vy+p11*vz+p15*vw;
    if(!Number.isFinite(cw)||Math.abs(cw)<1e-6)return null;
    const rx=(cx/cw+1)*halfWidth,ry=(cy/cw+1)*halfHeight,rz=-vz;
    return Number.isFinite(rx)&&Number.isFinite(ry)&&Number.isFinite(rz)?[rx,ry,rz]:null;
  };
}
