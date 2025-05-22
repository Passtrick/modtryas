package com.android.support;

import android.content.Context;
import java.io.File;

public class LibraryLoader {
    private static final String LIB_NAME = "libil2cpp.so";
    
    public static boolean loadLibrary(Context context) {
        try {
            File libFile = new File(context.getApplicationInfo().nativeLibraryDir + "/" + LIB_NAME);
            if (!libFile.exists()) {
                return false;
            }
            System.load(libFile.getAbsolutePath());
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
}