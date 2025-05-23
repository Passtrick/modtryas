package com.perfare.il2cppdumper;

import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {
    
    private ListView appListView;
    private Button dumpButton;
    private List<AppInfo> appsList = new ArrayList<>();
    private String selectedPackage = "";
    
    static {
        System.loadLibrary("il2cppdumper");
    }
    
    public native void dumpIl2Cpp(String packageName, String dataDir);
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        appListView = findViewById(R.id.appListView);
        dumpButton = findViewById(R.id.dumpButton);
        
        // Get installed apps
        appsList = PackageUtils.getInstalledApps(this);
        List<String> appNames = new ArrayList<>();
        for (AppInfo app : appsList) {
            appNames.add(app.getName());
        }
        
        ArrayAdapter<String> adapter = new ArrayAdapter<>(
            this, android.R.layout.simple_list_item_1, appNames);
        appListView.setAdapter(adapter);
        
        appListView.setOnItemClickListener((parent, view, position, id) -> {
            selectedPackage = appsList.get(position).getPackageName();
            Toast.makeText(MainActivity.this, 
                "Selected: " + appsList.get(position).getName(), 
                Toast.LENGTH_SHORT).show();
        });
        
        dumpButton.setOnClickListener(v -> {
            if (!selectedPackage.isEmpty()) {
                String dataDir = PackageUtils.getAppDataDir(this, selectedPackage);
                if (dataDir != null) {
                    new Thread(() -> {
                        dumpIl2Cpp(selectedPackage, dataDir);
                        runOnUiThread(() -> 
                            Toast.makeText(MainActivity.this, 
                                "Dump completed! Check /files/dump.cs", 
                                Toast.LENGTH_LONG).show());
                    }).start();
                } else {
                    Toast.makeText(this, 
                        "Failed to get app data directory", 
                        Toast.LENGTH_SHORT).show();
                }
            } else {
                Toast.makeText(this, 
                    "Please select an app first", 
                    Toast.LENGTH_SHORT).show();
            }
        });
    }
}