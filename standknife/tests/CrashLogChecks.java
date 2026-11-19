package dev.cloud.standknife;
public final class CrashLogChecks {
  public static void main(String[] arguments) {
    String input="DEBUG *** *** ***\nDEBUG pid: 99, tid: 99\nDEBUG unrelated\nDEBUG *** *** ***\nDEBUG pid: 23054, tid: 23054, name: UnityMain >>> com.neshurick.standknife <<<\nDEBUG signal 11 (SIGSEGV)\nDEBUG backtrace:\nDEBUG #00 pc 123456\nDEBUG *** *** ***\nDEBUG pid: 77, tid: 77\nDEBUG unrelated second\n";
    String result=LoaderService.targetCrash(input,"23054");
    if(!result.contains("SIGSEGV")||!result.contains("pc 123456")||result.contains("unrelated"))throw new AssertionError(result);
    String empty=LoaderService.targetCrash("DEBUG pid: 99, tid: 99\n","23054");
    if(!empty.startsWith("В crash-буфере"))throw new AssertionError(empty);
    String stale=LoaderService.targetCrash("DEBUG pid: 9115, tid: 11571 >>> com.neshurick.standknife <<<\nDEBUG Cmdline: com.neshurick.standknife\nDEBUG SIGSEGV\n","31698");
    if(!stale.startsWith("В crash-буфере"))throw new AssertionError(stale);
    System.out.println("Target crash extraction and missing-record checks passed.");
  }
}
