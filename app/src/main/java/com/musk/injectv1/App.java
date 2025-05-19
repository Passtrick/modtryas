package com.musk.injectv1;

import android.app.Application;
import com.topjohnwu.superuser.Shell;

public class App extends Application {

    @Override
    public void onCreate() {
        super.onCreate();
        // Inicializar Shell de Magisk
        Shell.enableVerboseLogging = true; // Para debug
        Shell.setDefaultBuilder(Shell.Builder.create()
            .setFlags(Shell.FLAG_MOUNT_MASTER)
            .setTimeout(10)
        );
        
        // Verificar root y SELinux
        initRoot();
    }

    private void initRoot() {
        Shell.su("setenforce 0").exec();
        Shell.su("magisk --daemon").exec();
    }
}