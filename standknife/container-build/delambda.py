# Build-only transformation: replaces the lambdas in LoaderService/MainActivity by anonymous classes, so dx
# (no d8 available here) emits a plain dex 037 without invoke-custom. Usage: delambda.py <src-dir> <out-dir>
import sys,os,shutil
src,out=sys.argv[1],sys.argv[2]
os.makedirs(out,exist_ok=True)
for name in os.listdir(src):
    shutil.copy(os.path.join(src,name),os.path.join(out,name))
def edit(path,pairs):
    s=open(path,encoding='utf-8').read()
    for old,new in pairs:
        assert s.count(old)==1,(path,s.count(old),old[:70])
        s=s.replace(old,new)
    open(path,'w',encoding='utf-8').write(s)
R='new Runnable(){public void run(){'
edit(os.path.join(out,'LoaderService.java'),[
 ('new Thread(()->runSession(),"cloud-session")','new Thread('+R+'runSession();}},"cloud-session")'),
 ('Thread reader=new Thread(()->{try(InputStream in=p.getInputStream()){byte[] b=new byte[4096];int n;while((n=in.read(b))>0)out.write(b,0,n);}catch(IOException ignored){}});',
  'Thread reader=new Thread('+R+'try(InputStream in=p.getInputStream()){byte[] b=new byte[4096];int n;while((n=in.read(b))>0)out.write(b,0,n);}catch(IOException ignored){}}});'),
 ('post(()->startActivity(launch));','post('+R+'startActivity(launch);}});'),
 ('new Thread(()->{try{Thread.sleep(20000);','new Thread('+R+'try{Thread.sleep(20000);'),
 ('}}catch(Exception e){log(e.toString());}},"cloud-diagnostics")','}}catch(Exception e){log(e.toString());}}},"cloud-diagnostics")'),
 ('new Thread(()->{try{stopOld();}catch(Exception ignored){}}).start()','new Thread('+R+'try{stopOld();}catch(Exception ignored){}}}).start()'),
])
C='new android.view.View.OnClickListener(){public void onClick(android.view.View v){'
edit(os.path.join(out,'MainActivity.java'),[
 ('start.setOnClickListener(v->{Intent i=new Intent(this,LoaderService.class);','start.setOnClickListener('+C+'Intent i=new Intent(MainActivity.this,LoaderService.class);'),
 ('status.setText("Запускаю службу. Разреши root, если появится запрос.");});','status.setText("Запускаю службу. Разреши root, если появится запрос.");}});'),
 ('startV8.setOnClickListener(v->{Intent i=new Intent(this,LoaderService.class).putExtra','startV8.setOnClickListener('+C+'Intent i=new Intent(MainActivity.this,LoaderService.class).putExtra'),
 ('status.setText("Запускаю службу с V8. Разреши root, если появится запрос.");});','status.setText("Запускаю службу с V8. Разреши root, если появится запрос.");}});'),
 ('log.setOnClickListener(v->showLog());','log.setOnClickListener('+C+'showLog();}});'),
 ('copy.setOnClickListener(v->{android.content.ClipboardManager','copy.setOnClickListener('+C+'android.content.ClipboardManager'),
 ('LoaderService.readLog(this)));Toast.makeText(this,"Журнал скопирован",Toast.LENGTH_SHORT).show();});','LoaderService.readLog(MainActivity.this)));Toast.makeText(MainActivity.this,"Журнал скопирован",Toast.LENGTH_SHORT).show();}});'),
 ('stop.setOnClickListener(v->{stopService(new Intent(this,LoaderService.class));','stop.setOnClickListener('+C+'stopService(new Intent(MainActivity.this,LoaderService.class));'),
 ('Для полного сброса закрой процесс игры.");});','Для полного сброса закрой процесс игры.");}});'),
])
print('delambda ok')
