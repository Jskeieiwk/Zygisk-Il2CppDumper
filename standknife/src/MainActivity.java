package dev.cloud.standknife;
import android.app.*;
import android.os.*;
import android.content.*;
import android.widget.*;
import java.io.*;

public class MainActivity extends Activity {
  TextView status;
  void showLog(){String text=LoaderService.readLog(this);status.setText(text.isEmpty()?"Журнал пока пуст.":text);}
  public void onCreate(Bundle b){
    super.onCreate(b);LinearLayout l=new LinearLayout(this);l.setOrientation(1);l.setPadding(32,48,32,32);ScrollView scroll=new ScrollView(this);scroll.addView(l);setContentView(scroll);
    TextView title=new TextView(this);title.setText("Cloud • StandKnife\nRoot loader v0.39");title.setTextSize(24);l.addView(title);
    TextView help=new TextView(this);help.setText("Игра 3.3 + root.\nНажатие на Cloud слева сверху открывает меню. ESP: сведения об игроках до 10 раз/сек; положение и проекция — по кадрам камеры. Для экономии ресурсов: Misc → Safe Mode. Новые функции проверяй по одной. Для Trigger/Silent/Force Shot подержи огонь из автомата без прицела: нужна калибровка. Hotkeys: уменьшение громкости открывает и закрывает меню. Если скрыть Cloud, Hotkeys включится автоматически. При следующем запуске Cloud снова появится. Настройки сохраняются. Серые пункты ещё не подключены.");l.addView(help);
    status=new TextView(this);status.setTextIsSelectable(true);
    Button start=new Button(this);start.setText("Запустить игру с модулем");l.addView(start);start.setOnClickListener(v->{Intent i=new Intent(this,LoaderService.class);if(Build.VERSION.SDK_INT>=26)startForegroundService(i);else startService(i);status.setText("Запускаю службу. Разреши root, если появится запрос.");});
    Button startV8=new Button(this);startV8.setText("Запустить с V8 (тест скорости)");l.addView(startV8);startV8.setOnClickListener(v->{Intent i=new Intent(this,LoaderService.class).putExtra("runtime","v8");if(Build.VERSION.SDK_INT>=26)startForegroundService(i);else startService(i);status.setText("Запускаю службу с V8. Разреши root, если появится запрос.");});
    Button log=new Button(this);log.setText("Обновить журнал");l.addView(log);log.setOnClickListener(v->showLog());
    Button copy=new Button(this);copy.setText("Скопировать журнал");l.addView(copy);copy.setOnClickListener(v->{android.content.ClipboardManager c=(android.content.ClipboardManager)getSystemService(CLIPBOARD_SERVICE);c.setPrimaryClip(ClipData.newPlainText("Cloud loader log",LoaderService.readLog(this)));Toast.makeText(this,"Журнал скопирован",Toast.LENGTH_SHORT).show();});
    Button stop=new Button(this);stop.setText("Остановить подключение");l.addView(stop);stop.setOnClickListener(v->{stopService(new Intent(this,LoaderService.class));status.setText("Служба остановлена. Для полного сброса закрой процесс игры.");});
    l.addView(status);showLog();
  }
  protected void onResume(){super.onResume();if(status!=null)showLog();}
}
