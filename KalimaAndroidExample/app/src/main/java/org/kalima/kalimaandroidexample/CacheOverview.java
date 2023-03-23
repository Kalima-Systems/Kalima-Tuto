package org.kalima.kalimaandroidexample;

import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.widget.ListView;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import org.kalima.androidlib.general.KMsgParcelable;
import org.kalima.androidlib.general.KalimaCacheCallback;
import org.kalima.androidlib.general.KalimaServiceAPI;
import org.kalima.androidlib.service.KalimaService;

import java.util.ArrayList;

public class CacheOverview extends AppCompatActivity {

    private ServiceConnection serviceConnection;
    private KalimaServiceAPI kalimaServiceAPI;
    private KalimaCacheCallback kalimaCacheCallback;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_cache_overview);
        final String addressName = getIntent().getStringExtra("address");

        final TextView cache = findViewById(R.id.tv_address);
        cache.setText(addressName);

        ListView entriesListView = findViewById(R.id.listview_cache_overview);
        final ArrayList<KMsgParcelable> messages = new ArrayList<>();
        final CacheOverviewAdapter adapter = new CacheOverviewAdapter(getApplicationContext(), new ArrayList<>());
        entriesListView.setAdapter(adapter);

        kalimaCacheCallback = new KalimaCacheCallback.Stub() {
            @Override
            public void onEntryUpdated(String address, KMsgParcelable kMsgParcelable) throws RemoteException {
                if(address.equals(addressName)) {
                    messages.remove(kMsgParcelable);
                    messages.add(kMsgParcelable);
                    runOnUiThread(() -> adapter.setMessages(messages));
                }
            }

            @Override
            public void onEntryDeleted(String address, String key) throws RemoteException {
                if(address.equals(addressName)) {
                    messages.remove(new KMsgParcelable(key, "".getBytes(), 0, -1, "".getBytes()));
                    runOnUiThread(() -> adapter.setMessages(messages));
                }
            }

            @Override
            public void onConnectionChanged(int status) throws RemoteException {

            }
        };

        serviceConnection = new ServiceConnection() {
            @Override
            public void onServiceConnected(ComponentName name, IBinder service) {
                kalimaServiceAPI = KalimaServiceAPI.Stub.asInterface(service);

                try {
                    kalimaServiceAPI.addKalimaCacheCallback(kalimaCacheCallback);
                    messages.clear();
                    messages.addAll(kalimaServiceAPI.getAll(addressName,  true, null));
                    runOnUiThread(() -> adapter.setMessages(messages));
                } catch (RemoteException e) {
                    e.printStackTrace();
                }
            }

            @Override
            public void onServiceDisconnected(ComponentName name) {

            }
        };

    }

    @Override
    protected void onResume() {
        super.onResume();
        Intent intent = new Intent(this, KalimaService.class);
        bindService(intent, serviceConnection, BIND_AUTO_CREATE);
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
}
