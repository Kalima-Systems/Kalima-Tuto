package org.kalima.kalimaandroidexample;

import static android.provider.Settings.ACTION_MANAGE_APP_ALL_FILES_ACCESS_PERMISSION;

import android.Manifest;
import android.app.ActivityManager;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;

import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import org.kalima.androidlib.general.KMsgParcelable;
import org.kalima.androidlib.general.KalimaCacheCallback;
import org.kalima.androidlib.general.KalimaServiceAPI;
import org.kalima.androidlib.general.KalimaServicePreferences;
import org.kalima.androidlib.service.KalimaService;

import java.util.ArrayList;
import java.util.Arrays;

public class MainActivity extends AppCompatActivity {

    private boolean permissionStorage = false;
    private ServiceConnection serviceConnection;
    private KalimaServiceAPI kalimaServiceAPI;
    private KalimaCacheCallback kalimaCacheCallback;
    private final String APP_NAME = "org.kalima.kalimaandroidexample";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ListView cachePathsListView = findViewById(R.id.cache_paths_list);
        final ArrayList<String> cachePathsList = new ArrayList<>();
        cachePathsList.add("/alarms/fire");
        cachePathsList.add("/sensors");
        final ArrayAdapter adapter = new ArrayAdapter(getApplicationContext(), R.layout.listview_cache_path, R.id.tv_cache_path, cachePathsList);
        cachePathsListView.setAdapter(adapter);

        final EditText editText = findViewById(R.id.edit_send);
        Button testSend = findViewById(R.id.test_send);
        testSend.setOnClickListener(v -> {
            try {
                // send message in cachePath /test with key "key"
                kalimaServiceAPI.set("/alarms/fire", "key", editText.getText().toString().getBytes(), "-1");
                editText.setText("");
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        });

        // Create android preferences to configure KalimaService for this app
        KalimaServicePreferences kalimaServicePreferences = KalimaServicePreferences.getInstance(getApplicationContext(), APP_NAME);
        kalimaServicePreferences.setNodeName("ExampleNode");
        // You need to choose an unused port
        kalimaServicePreferences.setServerPort(9150);
        // Notaries address and ports (ipAddress:port), separated with ","
        kalimaServicePreferences.setNotariesList("167.86.124.188:9090,62.171.130.233:9090,62.171.131.157:9090,144.91.108.243:9090");
        // Directory for Kalima files storage
        kalimaServicePreferences.setFilesPath(Environment.getExternalStorageDirectory().toString() + "/Kalima/jit/KalimaAndroidExample/");
        // Path for log directory
        kalimaServicePreferences.setLogPath(Environment.getExternalStorageDirectory().toString() + "/Kalima/jit/KalimaAndroidExample/");
        kalimaServicePreferences.setLedgerName("KalimaLedger");
        // Set list of CachePaths we want for notifications
        kalimaServicePreferences.setNotificationsCachePaths(new ArrayList<String>(Arrays.asList("/alarms/fire")));
        // Set class path of notification receiver
        // You will receive broadcast in this receiver when new data arrives in CachesPaths you choose with setNotificationsCachePaths
        // Then you can build a notification, even if the app is closed
        kalimaServicePreferences.setNotificationsReceiverClassPath("org.kalima.kalimaandroidexample.NotificationReceiver");

        adapter.notifyDataSetChanged();
        cachePathsListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Intent intent = new Intent(getApplicationContext(), CacheOverview.class);
                intent.putExtra("cachePath", cachePathsList.get(position));
                startActivity(intent);
            }
        });

        kalimaCacheCallback = new KalimaCacheCallback.Stub() {
            @Override
            // Callback for incoming data
            public void onEntryUpdated(String s, KMsgParcelable kMsgParcelable) throws RemoteException {
                Log.d("onEntryUpdated", "cachePath="  + s + ", key=" + kMsgParcelable.getKey());
            }

            // Callback for deleted data
            @Override
            public void onEntryDeleted(String s, String s1) throws RemoteException {
                Log.d("onEntryDeleted", "cachePath="  + s + ", key=" + s1);
            }

            @Override
            public void onConnectionChanged(int i) throws RemoteException {

            }
        };

        serviceConnection = new ServiceConnection() {

            @Override
            public void onServiceConnected(ComponentName name, IBinder service) {
                kalimaServiceAPI = KalimaServiceAPI.Stub.asInterface(service);
                try {
                    kalimaServiceAPI.addKalimaCacheCallback(kalimaCacheCallback);
                } catch (RemoteException e) {
                    e.printStackTrace();
                }

            }

            @Override
            public void onServiceDisconnected(ComponentName name) {

            }
        };

        checkPermissions();
        startService();
    }

    private void startService() {
        if (permissionStorage) {
            Intent intent = new Intent(MainActivity.this, KalimaService.class);
            intent.putExtra(KalimaService.APP_NAME, APP_NAME);
            if (!isMyServiceRunning()) {
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                    startForegroundService(intent);
                } else {
                    startService(intent);
                }
            }
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        if(permissionStorage) {
            Intent intent = new Intent(this, KalimaService.class);
            bindService(intent, serviceConnection, BIND_AUTO_CREATE);
        }
    }

    @Override
    protected void onPause() {
        if(kalimaServiceAPI != null) {
            try {
                kalimaServiceAPI.unregisterKlimaCacheCallback(kalimaCacheCallback);
                unbindService(serviceConnection);
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }
        super.onPause();
    }

    private void checkPermissions(){
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
            if(!Environment.isExternalStorageManager()) {
                Intent intent = new Intent(ACTION_MANAGE_APP_ALL_FILES_ACCESS_PERMISSION, Uri.parse("package:" + BuildConfig.APPLICATION_ID));
                ActivityResultLauncher<Intent> activityResult = registerForActivityResult(new ActivityResultContracts.StartActivityForResult(),
                        result -> {
                            if (Environment.isExternalStorageManager()) {
                                permissionStorage = true;
                                startService();
                            }
                        });
                activityResult.launch(intent);
            } else {
                permissionStorage = true;
                startService();
            }
        } else {
            if( ContextCompat.checkSelfPermission(getApplicationContext(), Manifest.permission.WRITE_EXTERNAL_STORAGE)!= PackageManager.PERMISSION_GRANTED){
                ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 0);
            }

            else{
                permissionStorage = true ;
                startService();
            }
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        if (requestCode == 0) {
            for (int i = 0; i < permissions.length; i++) {
                String permission = permissions[i];
                int grantResult = grantResults[i];

                if (permission.equals(Manifest.permission.WRITE_EXTERNAL_STORAGE)) {
                    if (grantResult == PackageManager.PERMISSION_GRANTED) {
                        permissionStorage = true ;
                        startService();
                    }
                }
            }
        }
    }

    private boolean isMyServiceRunning() {
        ActivityManager manager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        if (manager != null) {
            for (ActivityManager.RunningServiceInfo service : manager.getRunningServices(Integer.MAX_VALUE)) {
                if (KalimaService.class.getName().equals(service.service.getClassName())) {
                    return true;
                }
            }
        }
        return false;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so longa
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    private void set() throws RemoteException {
        // put message in kalima
        // param 1 : String CachePath
        // param 2 : String key
        // param 3 : byte[] body
        // param 4 : String ttl (not used yet)
        kalimaServiceAPI.set("StAubin/Ground_Floor/devices", "key", "hello world".getBytes(), "-1");
    }

    private void set2() throws RemoteException {
        // put message in kalima
        // param 1 : String CachePath
        // param 2 : KMsgParcelable kMsgParcelable
        KMsgParcelable kMsgParcelable = kalimaServiceAPI.get("StAubin/Ground_Floor/devices", "000425191801DBA9");
        kMsgParcelable.setBody("hello world".getBytes());
        kalimaServiceAPI.set2("StAubin/Ground_Floor/devices", kMsgParcelable);
    }

    private void delete() throws RemoteException {
        // delete an entry
        // param 1 : String CachePath
        // param 2 : String key
        kalimaServiceAPI.delete("StAubin/Ground_Floor/devices", "000425191801DBA9");
    }

    private void fillWindow() throws RemoteException {
        // get 10 first entries in StAubin/Ground_Floor/devices
        // param 1 : String CachePath
        // param 2 : int fromSequence
        /*
        param 3 : boolean reverseDirection
        false : fillWindow will return messages sort by lowest sequence to highest sequence
        true : fillWindow will return messages sort by highest sequence to lowest sequence
         */
        // param 4 : int windowSize (number of entries you want)
        kalimaServiceAPI.fillWindow("StAubin/Ground_Floor/devices", 0, false, 10, null);
    }

    private void get() throws RemoteException {
        // get record with key "k
        // ey" in cachePath "/test"
        KMsgParcelable kMsgParcelable = kalimaServiceAPI.get("/test", "key");
    }
}
