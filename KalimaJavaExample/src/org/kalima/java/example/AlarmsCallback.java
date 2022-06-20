package org.kalima.java.example;

import org.kalima.cache.lib.KMsg;
import org.kalima.kalimamq.message.KMessage;
import org.kalima.kalimamq.nodelib.MemCacheCallback;

public class AlarmsCallback implements MemCacheCallback {
	
	private String address;
	
	public AlarmsCallback(String address) {
		this.address = address;
	}

	@Override
	public String getAddress() {
		return address;
	}

	@Override
	public void putData(String key, KMessage kMessage) {
		KMsg kMsg = KMsg.setMessage(kMessage);
		System.out.println("new alarm key=" + key + " body=" + new String(kMsg.getBody()));
	}

	@Override
	public void removeData(String key) {

	}
}
