package uk.lgl.modmenu;

import android.app.Application;
import com.topjohnwu.superuser.Shell;

public class NepCaller extends Application {

    @Override
    public void onCreate() {
        super.onCreate();
        // Configura el shell
        Shell.Config.setFlags(Shell.FLAG_REDIRECT_STDERR);
        Shell.Config.verboseLogging(BuildConfig.DEBUG);

        // Inicializa Shell en el hilo principal
        Shell.getShell(shell -> {
            // Ejecuta comandos root
            shell.newJob().add("setenforce 0").submit();
        });
    }
}