package org.kalima.example.client;

import java.nio.channels.SocketChannel;
import java.util.concurrent.atomic.AtomicBoolean;

import org.kalima.cache.lib.KMsg;
import org.kalima.contractManager.ContractManager;
import org.kalima.kalimamq.message.KMessage;
import org.kalima.kalimamq.netlib.NioClient;
import org.kalima.kalimamq.nodelib.ClientCallback;
import org.kalima.kalimamq.nodelib.Node;
import org.kalima.util.Logger;

public class KalimaClientCallBack implements ClientCallback {
	
	private Client client;
	private Logger logger ;
	private Node node ; 
	private ContractManager contractManager;
		
	public KalimaClientCallBack(Client client) {
		this.client = client;
		this.node = client.getNode() ; 
		this.logger = node.getLogger();
		contractManager = new ContractManager(logger);
	}

	//isServer data received by a nioServer if true
	@Override
	public void putData(SocketChannel ch, KMessage msg) {
		KMsg kMsg = KMsg.setMessage(msg);
		if(kMsg.getType()!=KMsg.ADMIN) {
			client.getClone().set(kMsg.getCachePath(), kMsg, true, false);	
		}
	}

	@Override
	public void onConnectionChanged(int status, NioClient nioClient) {
		logger.log_srvMsg("ExampleClientNode", "KalimaClientCallBack", Logger.DEBUG, "onConnectionChanged status=" + status);
		client.getClone().onConnectedChange( (status==Node.CLIENT_STATUS_CONNECTED) ? new AtomicBoolean(true) : new AtomicBoolean(false), nioClient);
	}

	@Override
	public void onCacheDeleted(String cacheSubPath) {
		logger.log_srvMsg("ExampleClientNode", "KalimaClientCallBack", Logger.DEBUG, "onCacheDeleted cacheSubPath=" + cacheSubPath);
	}

	@Override
	public void putRequestData(SocketChannel ch, KMessage msg) {}

	@Override
	public void onNewVersion(int majver, int minver) {}

	@Override
	public void onNewCache(String cachePath) {
		client.getClone().addListnerForUpdate(new SmartContractCallback(cachePath, client, contractManager));		
	}
}