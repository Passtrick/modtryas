package com.perfare.il2cppdumper;

import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import java.util.ArrayList;
import java.util.List;

public class PackageUtils {
    
    public static List<AppInfo> getInstalledApps(Context context) {
        List<AppInfo> apps = new ArrayList<>();
        PackageManager pm = context.getPackageManager();
        List<ApplicationInfo> packages = pm.getInstalledApplications(PackageManager.GET_META_DATA);
        
        for (ApplicationInfo packageInfo : packages) {
            apps.add(new AppInfo(
                packageInfo.loadLabel(pm).toString(),
                packageInfo.packageName,
                packageInfo.sourceDir
            ));
        }
        return apps;
    }
    
    public static String getAppDataDir(Context context, String packageName) {
        try {
            PackageManager pm = context.getPackageManager();
            ApplicationInfo ai = pm.getApplicationInfo(packageName, 0);
            return ai.dataDir;
        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
            return null;
        }
    }
    
    public static class AppInfo {
        private String name;
        private String packageName;
        private String sourceDir;
        
        public AppInfo(String name, String packageName, String sourceDir) {
            this.name = name;
            this.packageName = packageName;
            this.sourceDir = sourceDir;
        }
        
        public String getName() { return name; }
        public String getPackageName() { return packageName; }
        public String getSourceDir() { return sourceDir; }
    }
}