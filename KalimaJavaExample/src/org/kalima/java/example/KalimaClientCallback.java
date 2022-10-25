package org.kalima.java.example;

import java.nio.channels.SocketChannel;

import org.kalima.cache.lib.Clone;
import org.kalima.kalimamq.message.KMessage;
import org.kalima.kalimamq.nodelib.ClientCallback;

public class KalimaClientCallback implements ClientCallback {
	
	private Clone clone;
	
	public KalimaClientCallback(Clone clone) {
		this.clone = clone;
	}

	@Override
	public void onCacheSynchronized(String address) {		
		if(address.equals("/sensors")) {
			clone.addMemCacheCallback(new SensorsCallBack(address, clone));
		} else if(address.equals("/alarms/fire")) {
			clone.addMemCacheCallback(new AlarmsCallback(address));
		}
	}

	@Override
	public void onNewCache(String address) {}

	@Override
	public void onNewVersion(int majver, int minver) {}

	@Override
	public void putRequestData(SocketChannel socketChannel, KMessage kMessage) {}

	@Override
	public void onReject(SocketChannel arg0) {
		System.out.println("You are not authorized on this Blockchain.");	
		System.out.println("Please contact an administrator");
		System.exit(-1);
	}

}
