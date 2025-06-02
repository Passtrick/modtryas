package com.android.support;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.provider.Settings;
import android.widget.Toast;

public class Main {
    private static final int OVERLAY_PERMISSION_REQ_CODE = 1001;

    static {
        System.loadLibrary("MyLibName");
    }

    private static native void CheckOverlayPermission(Context context);

    public static void StartWithoutPermission(Context context) {
        CrashHandler.init(context, true);
        if (context instanceof Activity) {
            Menu menu = new Menu(context);
            menu.SetWindowManagerActivity();
            
            if (checkMIUIPermission((Activity) context)) {
                menu.ShowMenu();
            }
        } else {
            CheckOverlayPermission(context);
        }
    }

    public static void Start(Context context) {
        CrashHandler.init(context, false);
        
        if (context instanceof Activity) {
            if (checkMIUIPermission((Activity) context)) {
                CheckOverlayPermission(context);
            }
        } else {
            CheckOverlayPermission(context);
        }
    }

    private static boolean checkMIUIPermission(Activity activity) {
        if (isMIUI() && !canDrawOverlays(activity)) {
            showMIUIPermissionDialog(activity);
            return false;
        }
        return true;
    }

    private static boolean isMIUI() {
        return Build.MANUFACTURER.equalsIgnoreCase("Xiaomi");
    }

    private static boolean canDrawOverlays(Context context) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            return Settings.canDrawOverlays(context);
        }
        return true;
    }

    private static void showMIUIPermissionDialog(final Activity activity) {
        AlertDialog.Builder builder = new AlertDialog.Builder(activity);
        builder.setTitle("Permiso Requerido en Xiaomi");
        builder.setMessage("Para funcionar correctamente en dispositivos Xiaomi, necesitas activar manualmente el permiso 'Mostrar sobre otras apps'.\n\n¿Quieres ir a la configuración ahora?");
        builder.setPositiveButton("Sí", (dialog, which) -> {
            try {
                // Intent especial para MIUI
                Intent intent = new Intent("miui.intent.action.APP_PERM_EDITOR");
                intent.setClassName("com.miui.securitycenter",
                        "com.miui.permcenter.permissions.PermissionsEditorActivity");
                intent.putExtra("extra_pkgname", activity.getPackageName());
                activity.startActivityForResult(intent, OVERLAY_PERMISSION_REQ_CODE);
            } catch (Exception e) {
                // Fallback al método estándar
                Intent intent = new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION,
                        Uri.parse("package:" + activity.getPackageName()));
                activity.startActivityForResult(intent, OVERLAY_PERMISSION_REQ_CODE);
            }
        });
        builder.setNegativeButton("No", null);
        builder.setCancelable(false);
        builder.show();
    }

    // Método para llamar desde JNI cuando CheckOverlayPermission es invocado
    public static void onCheckOverlayPermission(Context context) {
        if (context instanceof Activity) {
            ((Activity) context).runOnUiThread(() -> {
                if (isMIUI()) {
                    showMIUIPermissionDialog((Activity) context);
                } else {
                    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                        Intent intent = new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION,
                                Uri.parse("package:" + context.getPackageName()));
                        ((Activity) context).startActivityForResult(intent, OVERLAY_PERMISSION_REQ_CODE);
                    }
                }
            });
        }
    }
}