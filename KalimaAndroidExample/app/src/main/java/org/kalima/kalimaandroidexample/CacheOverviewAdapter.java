package org.kalima.kalimaandroidexample;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import org.kalima.androidlib.general.KMsgParcelable;

import java.util.ArrayList;

public class CacheOverviewAdapter extends BaseAdapter {

    ArrayList<KMsgParcelable> messages;
    LayoutInflater inflater;

    public CacheOverviewAdapter(Context context, ArrayList<KMsgParcelable> messages) {
        this.messages = messages;
        this.inflater = LayoutInflater.from(context);
    }

    @Override
    public int getCount() {
        return messages.size();
    }

    @Override
    public Object getItem(int position) {
        return messages.get(position);
    }

    @Override
    public long getItemId(int position) {
        return 0;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        convertView = inflater.inflate(R.layout.listview_cache_overview, null);
        TextView key = convertView.findViewById(R.id.tv_key);
        TextView body = convertView.findViewById(R.id.tv_body);
        key.setText(messages.get(position).getKey());
        body.setText(new String(messages.get(position).getBody()));
        return convertView;
    }

    public void setMessages(ArrayList<KMsgParcelable> messages) {
        this.messages.clear();
        this.messages.addAll(messages);
        this.notifyDataSetChanged();
    }
}
