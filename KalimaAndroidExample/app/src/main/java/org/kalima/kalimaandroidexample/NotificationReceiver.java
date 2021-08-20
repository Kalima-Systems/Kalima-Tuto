package org.kalima.kalimaandroidexample;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.util.Log;

import androidx.core.app.NotificationCompat;
import androidx.core.app.NotificationManagerCompat;

import org.kalima.androidlib.general.KMsgParcelable;
import org.kalima.androidlib.service.KalimaService;

public class NotificationReceiver extends BroadcastReceiver {

    /*
    With this class, you can launch notifications even if your app is closed.
    To achieve that, you need to declare this receiver in your Manifest file.
    See example in AndroidManifest.xml.
     */

    private final String CHANNEL_ID = "org.kalima.kalimandroidexample.notifications";
    private static int NOTIFICATION_ID = 0;

    @Override
    public void onReceive(Context context, Intent intent) {
        KMsgParcelable kMsgParcelable = intent.getParcelableExtra(KalimaService.EXTRA_MSG);
        String cachePath = intent.getStringExtra(KalimaService.EXTRA_CACHE_PATH);
        Log.d("notification", "cachePath=" + cachePath + " key=" + kMsgParcelable.getKey());

        // You can choose an activity to start, when user click on notification
        Intent dialogIntent = new Intent(context, MainActivity.class);
        PendingIntent pendingIntent = PendingIntent.getActivity(context, 0, dialogIntent, 0);
        createNotificationChannel(context);

        NotificationCompat.Builder builder = new NotificationCompat.Builder(context, CHANNEL_ID)
                .setSmallIcon(android.R.drawable.stat_sys_warning)
                .setContentTitle(cachePath)
                .setContentText(kMsgParcelable.getKey() + " value=" + new String(kMsgParcelable.getBody()))
                .setContentIntent(pendingIntent)
                .setAutoCancel(true)
                .setPriority(NotificationCompat.PRIORITY_HIGH);

        NotificationManagerCompat notificationManager = NotificationManagerCompat.from(context);
        notificationManager.notify(NOTIFICATION_ID, builder.build());
        NOTIFICATION_ID++;
    }

    private void createNotificationChannel(Context context) {
        // Create the NotificationChannel, but only on API 26+ because
        // the NotificationChannel class is new and not in the support library
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            String description = "Alarms channel";
            int importance = NotificationManager.IMPORTANCE_HIGH;
            NotificationChannel channel = new NotificationChannel(CHANNEL_ID, CHANNEL_ID, importance);
            channel.setDescription(description);
            // Register the channel with the system; you can't change the importance
            // or other notification behaviors after this
            NotificationManager notificationManager = context.getSystemService(NotificationManager.class);
            notificationManager.createNotificationChannel(channel);
        }
    }
}
