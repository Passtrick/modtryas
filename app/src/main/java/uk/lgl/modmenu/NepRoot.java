package uk.lgl.modmenu;

import android.app.AlertDialog;
import android.app.Activity;
import com.topjohnwu.superuser.Shell;
import uk.lgl.MainActivity;
import java.util.List;

public class NepRoot extends Activity {
    
    public static native int Init();
    
    private MainActivity thiz;
    
    public NepRoot(MainActivity thiz) {
        this.thiz = thiz;
    }
    
    public void showNoRootMessage() {
        new AlertDialog.Builder(thiz)
            .setMessage("Could not acquire root")
            .setNegativeButton(android.R.string.ok, null)
            .show();
    }
    
    public int Game(String pkg) {
        try {
            List<String> output = Shell.cmd("(toolbox ps; toolbox ps -A; toybox ps; toybox ps -A) | grep \" " + pkg + "$\"").exec().getOut();
            for (String line : output) {
                String[] parts = line.trim().split("\\s+");
                if (parts.length >= 2) {
                    return Integer.parseInt(parts[1]);
                }
            }
            return -1;
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }
}