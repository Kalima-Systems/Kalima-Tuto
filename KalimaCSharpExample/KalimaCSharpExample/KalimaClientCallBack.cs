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

		public KalimaClientCallBack (Client client)
		{
			this.client = client;
			this.logger = client.getLogger();
		}

		public void putRequestData(SocketChannel ch, KMessage msg) {}

		public void onNewVersion(int majver, int minver) {}

		public void onNewCache(String address) {}

		public void onCacheSynchronized(string address)
		{
			if (address.Equals("/sensors"))
            {
				client.getClone().addListnerForUpdate(new SensorsCallback(address, client.getClone()));
			} else if (address.Equals("/alarms/fire"))
            {
				client.getClone().addListnerForUpdate(new AlarmsCallback(address));
            }
	
		}
    }
}

