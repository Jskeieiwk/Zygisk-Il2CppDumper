package com.cloudcrack.oxide.external;

import android.content.Context;
import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;

final class DiagnosticLog {
    private static boolean installed;
    private DiagnosticLog() {}
    static synchronized void install(Context context) {
        if(installed)return;
        installed=true;
        final Context app=context.getApplicationContext();
        final Thread.UncaughtExceptionHandler previous=Thread.getDefaultUncaughtExceptionHandler();
        Thread.setDefaultUncaughtExceptionHandler((thread,error)->{
            StringWriter stack=new StringWriter();error.printStackTrace(new PrintWriter(stack));
            write(app,"CRASH "+thread.getName()+"\n"+stack);
            if(previous!=null)previous.uncaughtException(thread,error);
        });
    }
    static synchronized void write(Context context,String message) {
        try {
            File file=new File(context.getFilesDir(),"last-run.log");
            if(file.length()>65536)Files.deleteIfExists(file.toPath());
            try(FileOutputStream out=new FileOutputStream(file,true)){
                out.write((System.currentTimeMillis()+" "+message+"\n").getBytes(StandardCharsets.UTF_8));
            }
        }catch(Exception ignored){}
    }
    static String read(Context context) {
        try {return new String(Files.readAllBytes(new File(context.getFilesDir(),"last-run.log").toPath()),StandardCharsets.UTF_8);}
        catch(Exception error){return "Журнал пока пуст: "+error.getMessage();}
    }
}
