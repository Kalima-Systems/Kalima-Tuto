package org.kalima.example.client;

import java.nio.channels.SocketChannel;

import org.kalima.kalimamq.message.KMessage;
import org.kalima.kalimamq.nodelib.Node;
import org.kalima.kalimamq.nodelib.ServerCallback;

public class KalimaServerCallBack implements ServerCallback {

	public KalimaServerCallBack() {	}

	@Override
	public void putData(SocketChannel socket, KMessage kMessage) {}

	@Override
	public void processSnapshot(SocketChannel ch, KMessage kMessage) {}

	@Override
	public void disconnected(String name, int port) {}

	@Override
	public void nodeAcked(String nodeName, String hostName, int port) {}

	@Override
	public void nodeDisconnected(Node node, boolean b) {}

	@Override
	public void nodeConnected(Node node) {}

	@Override
	public void onConnectionChanged(int status) {}

	@Override
	public void addCache(String cachePath) {}

	@Override
	public void removeCache(String cachePath) {}

	@Override
	public void processSnapshot(SocketChannel soc, String cachePathSeqs) {}

	@Override
	public KMessage processNextMessage(KMessage msg, SocketChannel soc) {
		return null;
	}

	@Override
	public void onVoteDone(boolean isLeader) {
		// TODO Auto-generated method stub
		
	}
}
