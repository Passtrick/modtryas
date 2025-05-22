package com.android.support;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Handler;
import android.provider.Settings;
import android.widget.Toast;

public class Main {
    static {
        System.loadLibrary("MyLibName");
    }

    private static native void CheckOverlayPermission(Context context);

    public static void Start(Context context) {
        if (!LibraryLoader.loadLibrary(context)) {
            Toast.makeText(context, "Target library not found", Toast.LENGTH_SHORT).show();
            return;
        }
        
        CrashHandler.init(context, false);
        CheckOverlayPermission(context);
    }

    public static void StartWithoutPermission(Context context) {
        if (!LibraryLoader.loadLibrary(context)) {
            Toast.makeText(context, "Target library not found", Toast.LENGTH_SHORT).show();
            return;
        }
        
        CrashHandler.init(context, true);
        Menu menu = new Menu(context);
        menu.SetWindowManagerActivity();
        menu.ShowMenu();
    }
}