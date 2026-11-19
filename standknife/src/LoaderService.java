package dev.cloud.standknife;
import android.app.*;
import android.os.*;
import android.content.*;
import android.content.pm.*;
import java.io.*;
import java.util.concurrent.TimeUnit;

public class LoaderService extends Service {
  static final String GAME="com.neshurick.standknife",DIR="/data/local/tmp/cloud-standknife";
  volatile boolean running=false,stopping=false;
  java.lang.Process injector;
  boolean menuReady=false,nativeReady=false,connectionAnnounced=false;
  volatile boolean useV8=false;
  public IBinder onBind(Intent i){return null;}
  public static String readLog(Context c){try{byte[] b=new byte[(int)Math.min(new File(c.getFilesDir(),"session.log").length(),262144)];try(FileInputStream in=new FileInputStream(new File(c.getFilesDir(),"session.log"))){int n=in.read(b);return n<0?"":new String(b,0,n,"UTF-8");}}catch(Exception e){return "";}}
  synchronized void log(String s){try(FileOutputStream out=new FileOutputStream(new File(getFilesDir(),"session.log"),true)){out.write((s+"\n").getBytes("UTF-8"));}catch(Exception ignored){}}
  Notification notification(String text){
    String channel="cloud_connection";NotificationManager nm=(NotificationManager)getSystemService(NOTIFICATION_SERVICE);
    if(Build.VERSION.SDK_INT>=26)nm.createNotificationChannel(new NotificationChannel(channel,"Подключение к игре",NotificationManager.IMPORTANCE_LOW));
    PendingIntent pi=PendingIntent.getActivity(this,0,new Intent(this,MainActivity.class),PendingIntent.FLAG_UPDATE_CURRENT|PendingIntent.FLAG_IMMUTABLE);
    Notification.Builder b=Build.VERSION.SDK_INT>=26?new Notification.Builder(this,channel):new Notification.Builder(this);
    return b.setSmallIcon(android.R.drawable.ic_menu_info_details).setContentTitle("Cloud StandKnife Loader").setContentText(text).setContentIntent(pi).setOngoing(true).build();
  }
  void state(String s){log(s);((NotificationManager)getSystemService(NOTIFICATION_SERVICE)).notify(17,notification(s));}
  public int onStartCommand(Intent i,int f,int id){startForeground(17,notification("Подготовка подключения"));if(!running){useV8=i!=null&&"v8".equals(i.getStringExtra("runtime"));running=true;new Thread(()->runSession(),"cloud-session").start();}return START_NOT_STICKY;}
  String root(String cmd)throws Exception{
    java.lang.Process p=new ProcessBuilder("su","-c",cmd).redirectErrorStream(true).start();
    ByteArrayOutputStream out=new ByteArrayOutputStream();Thread reader=new Thread(()->{try(InputStream in=p.getInputStream()){byte[] b=new byte[4096];int n;while((n=in.read(b))>0)out.write(b,0,n);}catch(IOException ignored){}});reader.start();
    if(!p.waitFor(90,TimeUnit.SECONDS)){p.destroy();throw new IOException("Таймаут su: нет ответа от root");}reader.join(2000);
    String s=out.toString("UTF-8");if(p.exitValue()!=0)throw new IOException("su exit="+p.exitValue()+": "+s);return s;
  }
  void copy(String n)throws IOException{try(InputStream in=getAssets().open(n);OutputStream out=new FileOutputStream(new File(getFilesDir(),n))){byte[] b=new byte[65536];int count;while((count=in.read(b))>0)out.write(b,0,count);}}
  static String targetCrash(String text,String pid){
    StringBuilder result=new StringBuilder();boolean selected=false;int count=0;
    for(String line:text.split("\n")){
      if(selected&&line.contains("*** *** ***"))break;
      if(line.contains("pid: "+pid+",")||line.contains("pid:"+pid+","))selected=true;
      if(selected&&count++<120)result.append(line).append('\n');
    }
    return result.length()==0?"В crash-буфере нет записи этого процесса":result.toString();
  }
  void crashDiagnostics(String pid){
    try{
      String crash=targetCrash(root("logcat -b crash -d -t 240 -v threadtime 2>/dev/null || true"),pid);
      if(crash.startsWith("В crash-буфере")){Thread.sleep(500);crash=targetCrash(root("logcat -b crash -d -t 240 -v threadtime 2>/dev/null || true"),pid);}
      log("Target crash buffer:\n"+crash);
      log("Target system events:\n"+root("logcat -b system -b events -d -t 400 -v brief 2>/dev/null | /system/bin/grep -E '"+pid+"|"+GAME+"' | tail -n 60 || true"));
    }catch(Exception error){log("Crash diagnostics unavailable: "+error.getMessage());}
  }
  void stopOld()throws Exception{root("p=$(cat "+DIR+"/pid 2>/dev/null); case \"$p\" in ''|*[!0-9]*) ;; *) if tr '\\000' ' ' </proc/$p/cmdline 2>/dev/null | /system/bin/grep -q '"+DIR+"/inject'; then kill \"$p\"; fi ;; esac; rm -f "+DIR+"/pid");}
  void runSession(){
    try{
      new FileOutputStream(new File(getFilesDir(),"session.log")).close();
      log("Cloud v0.45 / Frida 17.26.3\nDevice: "+Build.MANUFACTURER+" "+Build.MODEL+"\nAndroid: "+Build.VERSION.RELEASE+" SDK "+Build.VERSION.SDK_INT+"\nABIs: "+java.util.Arrays.toString(Build.SUPPORTED_ABIS));
      PackageInfo info=getPackageManager().getPackageInfo(GAME,0);log("Game: "+info.versionName+" / "+info.versionCode);
      if(!"3.3".equals(info.versionName))throw new IOException("Нужна игра 3.3");
      state("Проверка root…");String uid=root("id");log(uid);if(!uid.contains("uid=0"))throw new IOException("su не выдал root");
      log("SELinux: "+root("getenforce 2>/dev/null || true").trim());stopOld();
      final Intent launch=getPackageManager().getLaunchIntentForPackage(GAME);if(launch==null)throw new IOException("Нет экрана запуска игры");launch.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);new Handler(getMainLooper()).post(()->startActivity(launch));
      state("Ожидание загрузки Unity…");String pid="",maps="";
      for(int t=0;t<90&&!stopping;t++){
        String found=root("pidof "+GAME+" || true").trim();
        if(found.matches("[0-9]+")){pid=found;maps=root("cat /proc/"+pid+"/maps 2>/dev/null || true");if(maps.contains("libmain.so")&&maps.contains("libart.so"))break;}
        Thread.sleep(1000);
      }
      if(stopping)return;
      if(!maps.contains("libmain.so"))throw new IOException("libmain.so не загружена за 90 секунд");
      String exe=root("readlink /proc/"+pid+"/exe").trim();String bits=root("od -An -tu1 -j4 -N1 /proc/"+pid+"/exe").trim();
      String abi;if("2".equals(bits))abi="arm64";else if("1".equals(bits))abi="arm";else throw new IOException("Не удалось определить ELF-разрядность процесса: "+bits);
      log("PID: "+pid+"\nExecutable: "+exe+"\nELF: "+bits+" / injector "+abi);
      Thread.sleep(2000);copy("inject-"+abi);copy("module.js");String local=getFilesDir().getAbsolutePath();
      root("mkdir -p "+DIR+" && chmod 700 "+DIR+" && cp "+local+"/inject-"+abi+" "+DIR+"/inject && cp "+local+"/module.js "+DIR+"/module.js && chmod 700 "+DIR+"/inject");
      log("Injector: "+root(DIR+"/inject --version").trim());String runtimeFlag="";
      if(useV8){
        String help=root(DIR+"/inject --help 2>&1 || true");
        if(help.contains("--runtime")){runtimeFlag=" --runtime=v8";log("JS runtime requested: V8");}
        else log("JS runtime: V8 requested, but this injector has no --runtime option; using its default");
      }else log("JS runtime requested: injector default");
      state("Подключение к процессу игры…");
      injector=new ProcessBuilder("su","-c","echo $$ > "+DIR+"/pid; exec "+DIR+"/inject -p "+pid+" -s "+DIR+"/module.js"+runtimeFlag).redirectErrorStream(true).start();
      final String targetPid=pid;
      new Thread(()->{try{Thread.sleep(20000);if(running&&!stopping&&(!menuReady||!nativeReady)){log("Нет полного подтверждения подключения за 20 секунд. menu="+menuReady+" native="+nativeReady);log("Target alive: "+root("kill -0 "+targetPid+" 2>/dev/null && echo yes || echo no"));log("Recent system errors:\n"+root("logcat -d -t 150 -v brief 2>/dev/null | /system/bin/grep -E 'avc:|Fatal|frida|libart|crash|linker' | tail -n 30 || true"));}}catch(Exception e){log(e.toString());}},"cloud-diagnostics").start();
      try(BufferedReader reader=new BufferedReader(new InputStreamReader(injector.getInputStream()))){String line;while((line=reader.readLine())!=null){log(line);if(line.contains("CLOUD:menu-ready"))menuReady=true;if(line.contains("CLOUD:il2cpp-ready"))nativeReady=true;if(line.contains("CLOUD:module-not-ready")||line.contains("CLOUD:module-unavailable")){nativeReady=false;connectionAnnounced=false;state("Игровой модуль не готов. Причина указана в журнале.");}if(menuReady&&nativeReady&&!connectionAnnounced){connectionAnnounced=true;state("Меню и модуль подключены");}}}
      int exit=injector.waitFor();if(!stopping){crashDiagnostics(pid);state("Подключение завершилось, код "+exit+". Скопируй журнал.");log("Target alive after exit: "+root("kill -0 "+pid+" 2>/dev/null && echo yes || echo no"));log("Recent system errors:\n"+root("logcat -d -t 150 -v brief 2>/dev/null | /system/bin/grep -E 'avc:|Fatal|frida|libart|crash|linker' | tail -n 30 || true"));}
    }catch(Exception e){state("Ошибка подключения: "+e.getMessage());}
    finally{running=false;stopForeground(false);stopSelf();}
  }
  public void onDestroy(){stopping=true;if(injector!=null)injector.destroy();new Thread(()->{try{stopOld();}catch(Exception ignored){}}).start();super.onDestroy();}
}
