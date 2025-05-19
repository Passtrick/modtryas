package uk.lgl.modmenu;

import android.app.Application;
import com.topjohnwu.superuser.Shell;
import uk.lgl.BuildConfig;

public class NepCaller extends Application {

    static {
        // Configura el shell antes de que se cree la clase
        Shell.enableVerboseLogging = BuildConfig.DEBUG;
        Shell.setDefaultBuilder(Shell.Builder.create()
            .setFlags(Shell.FLAG_REDIRECT_STDERR)
            .setTimeout(10));
    }

    @Override
    public void onCreate() {
        super.onCreate();
        
        // Inicializa Shell en el hilo principal
        Shell.getShell(shell -> {
            shell.newJob().add("setenforce 0").submit();
        });
    }
}