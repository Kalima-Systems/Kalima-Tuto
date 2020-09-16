using System;
using org.kalima.kalimamq.message;
using org.kalima.kalimamq.nodelib;
using org.kalima.kalimamq.netlib;
using org.kalima.util;
using org.kalima.cache.lib;
using java.util.concurrent.atomic;
using java.nio.channels;

namespace KalimaCSharpExample
{
	public class KalimaClientCallBack : ClientCallback
	{

		private Client client;
		private Logger logger;
		private Node node;

		public KalimaClientCallBack (Client client)
		{
			this.client = client;
			this.node = client.getNode ();
			this.logger = node.getLogger ();
		}

		public void putData(SocketChannel ch, KMessage msg) {
			KMsg kMsg = KMsg.setMessage (msg);
			client.getClone ().set (kMsg.getCachePath(), kMsg, true, false);
		}

		public void onConnectionChanged(int status, NioClient nioClient){
			logger.log_srvMsg ("ExampleClientNode", "KalimaClientCallBack", Logger.DEBUG, "onConnectionChanged status=" + status);
			client.getClone().onConnectedChange( (status==Node.CLIENT_STATUS_CONNECTED) ? new AtomicBoolean(true) : new AtomicBoolean(false), nioClient);
		}

		public void onCacheDeleted (string cacheSubPath){
			logger.log_srvMsg ("ExampleClientNode", "KalimaClientCallBack", Logger.DEBUG, "onCacheDeleted cacheSubPath=" + cacheSubPath);
		}

		public void putRequestData(SocketChannel ch, KMessage msg) {}

		public void onNewVersion(int majver, int minver) {}

		public void onNewCache(String cachePath) {}
	}
}

