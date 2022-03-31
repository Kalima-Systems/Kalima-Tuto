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
		private SendTimeout sendTimeout;

		public KalimaClientCallBack (Client client)
		{
			this.client = client;
			this.node = client.getNode ();
			this.logger = node.getLogger ();
			sendTimeout = new SendTimeout(client.getClone().getClonePreferences().getLoadConfig().getSendTimeout(), logger, node);
		}

		public void putData(SocketChannel ch, KMessage msg) {
			KMsg kMsg = KMsg.setMessage (msg);
			sendTimeout.remove(kMsg);
			client.getClone ().set (kMsg.getCachePath(), kMsg, true, false);
			if (kMsg.getType() == KMessage.PUB)
			{
				Console.WriteLine("putData cachePath=" + kMsg.getCachePath() + " key=" + kMsg.getKey() + " body=" + System.Text.Encoding.Default.GetString(kMsg.getBody()));
			}
		}

		public void onConnectionChanged(int status, NioClient nioClient){
			logger.log_srvMsg ("ExampleClientNode", "KalimaClientCallBack", Logger.DEBUG, "onConnectionChanged status=" + status);
			client.getClone().onConnectedChange( (status==Node.CLIENT_STATUS_CONNECTED) ? new AtomicBoolean(true) : new AtomicBoolean(false), nioClient, false);
		}

		public void OnCacheDeleted(string cachesubPath)
        {
			logger.log_srvMsg("ExampleClientNode", "KalimaClientCallBack", Logger.DEBUG, "onCachDeleted cacheSubPath=" + cachesubPath);
        }

		public void putRequestData(SocketChannel ch, KMessage msg) {}

		public void onNewVersion(int majver, int minver) {}

		public void onNewCache(String cachePath) {}

        public void onCacheSynchronized(string str)
        {}

        public void send(KMessage km)
        {
			sendTimeout.put(KMsg.setMessage(km));
		}

        public void onJoined(SocketChannel sc, KMessage km)
        {
			client.getClone().onJoined(sc, false);
        }
    }
}

