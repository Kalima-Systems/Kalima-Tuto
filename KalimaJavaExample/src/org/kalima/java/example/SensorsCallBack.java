package org.kalima.java.example;

import org.kalima.cache.lib.Clone;
import org.kalima.cache.lib.KMsg;
import org.kalima.kalimamq.message.KMessage;
import org.kalima.kalimamq.nodelib.MemCacheCallback;

public class SensorsCallBack implements MemCacheCallback{
	
	private String address;
	private Clone clone;
	
	public SensorsCallBack(String address, Clone clone) {
		this.address = address;
		this.clone = clone;
	}
	
	@Override
	public void putData(KMessage kMessage) {
		KMsg msg = KMsg.setMessage(kMessage);
		String key = msg.getKey();
		System.out.println("new sensor value key=" + key + " body=" + new String(msg.getBody()));
		if(key.equals("temperature")) {
			int temperature = Integer.parseInt(new String(msg.getBody()));
			if(temperature >= 100) {
				clone.put("/alarms/fire", "temperature", ("Temperature too high: " + temperature + " °C").getBytes());
			}
		}
	}

	@Override
	public void removeData(KMessage kMessage) {
		
	}
	
	@Override
	public String getAddress() {
		return address;
	}
}
