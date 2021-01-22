using System;
using org.kalima.kalimamq.nodelib;
using org.kalima.kalimamq.message;
using java.nio.channels;

namespace KalimaCSharpExample
{
	public class KalimaServerCallBack : ServerCallback
	{
		public KalimaServerCallBack (){}

		public void putData(SocketChannel socket, KMessage kMessage) {}
			
		public void processSnapshot(SocketChannel ch, KMessage kMessage) {}

		public void disconnected(String name, int port) {}
	
		public void nodeAcked(String nodeName, String hostName, int port) {}

		public void nodeDisconnected(Node node, bool b) {}
	
		public void nodeConnected(Node node) {}

		public void onConnectionChanged(int status) {}

		public void addCache(String cachePath) {}
			
		public void removeCache(String cachePath) {}

		public void processSnapshot(SocketChannel soc, String cachePathSeqs, bool fromNotaryNode) {}
			
		public KMessage processNextMessage(KMessage msg) {
			return null;
		}
			
		public void onVoteDone(bool isLeader) {}
	}
}

