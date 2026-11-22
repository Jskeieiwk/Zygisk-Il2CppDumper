package com.cloud.crack.berda

import android.os.Build
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.ScrollView
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import java.io.BufferedReader
import java.io.DataOutputStream
import java.io.File
import java.io.InputStreamReader

class MainActivity : AppCompatActivity() {

    private lateinit var btn: Button
    private lateinit var log: TextView
    private lateinit var status: TextView

    private val target = "com.heesoyam.berda"

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        btn    = findViewById(R.id.btnInject)
        log    = findViewById(R.id.log)
        status = findViewById(R.id.status)

        status.text = getString(R.string.status_idle)
        append("Cloud Crack 67 — Berda Survival injector")
        append("Target: $target")
        append("ABI: ${Build.SUPPORTED_ABIS.joinToString(",")}")
        append("Native dir: ${applicationInfo.nativeLibraryDir}")

        btn.setOnClickListener {
            btn.isEnabled = false
            status.text = getString(R.string.status_working)
            CoroutineScope(Dispatchers.IO).launch {
                val result = runCatching { inject() }
                withContext(Dispatchers.Main) {
                    btn.isEnabled = true
                    result.onSuccess { msg ->
                        status.text = getString(R.string.status_done)
                        append("✓ $msg")
                    }.onFailure { e ->
                        status.text = getString(R.string.status_failed)
                        append("✗ ${e.message}")
                    }
                    (findViewById<ScrollView>(R.id.scroll))
                        .post { findViewById<ScrollView>(R.id.scroll).fullScroll(View.FOCUS_DOWN) }
                }
            }
        }
    }

    private fun append(line: String) {
        runOnUiThread { log.append(line + "\n") }
    }

    private fun inject(): String {
        val nativeDir = applicationInfo.nativeLibraryDir
        val payload   = "$nativeDir/libcloud_cheat.so"
        val injector  = "$nativeDir/libcloud_injector.so"

        if (!File(payload).exists())  throw RuntimeException("payload missing: $payload")
        if (!File(injector).exists()) throw RuntimeException("injector missing: $injector")

        val script = buildString {
            append("set -e\n")
            // Stage files in /data/local/tmp (universally executable by root).
            append("cp -f '$injector' /data/local/tmp/cloud_injector\n")
            append("cp -f '$payload'  /data/local/tmp/libcloud_cheat.so\n")
            append("chmod 0755 /data/local/tmp/cloud_injector /data/local/tmp/libcloud_cheat.so\n")
            append("chcon u:object_r:system_file:s0 /data/local/tmp/cloud_injector 2>/dev/null || true\n")
            append("chcon u:object_r:system_file:s0 /data/local/tmp/libcloud_cheat.so 2>/dev/null || true\n")
            // Resolve target PID.
            append("PID=$(pidof $target | awk '{print \$1}')\n")
            append("if [ -z \"$PID\" ]; then echo 'target_not_running'; exit 7; fi\n")
            append("echo \"pid=$PID\"\n")
            // Fire.
            append("/data/local/tmp/cloud_injector \"$PID\" /data/local/tmp/libcloud_cheat.so\n")
        }

        val out = runRoot(script)
        if (out.second != 0) throw RuntimeException("su failed (exit=${out.second}):\n${out.first}")
        append(out.first)
        return "injected into $target"
    }

    /** Pipe `script` into `su` and return (output, exitCode). */
    private fun runRoot(script: String): Pair<String, Int> {
        val proc = ProcessBuilder("su")
            .redirectErrorStream(true)
            .start()
        DataOutputStream(proc.outputStream).use { it.writeBytes(script); it.writeBytes("\nexit $?\n"); it.flush() }
        val reader = BufferedReader(InputStreamReader(proc.inputStream))
        val sb = StringBuilder()
        var line = reader.readLine()
        while (line != null) { sb.appendLine(line); line = reader.readLine() }
        val exit = proc.waitFor()
        return Pair(sb.toString(), exit)
    }
}
