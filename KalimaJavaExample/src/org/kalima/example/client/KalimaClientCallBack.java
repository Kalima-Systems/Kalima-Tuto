package org.kalima.example.client;

import java.nio.channels.SocketChannel;
import java.util.concurrent.atomic.AtomicBoolean;

import org.kalima.cache.lib.CacheComparator;
import org.kalima.cache.lib.KMsg;
import org.kalima.cache.lib.SendTimeout;
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
	private String gitUser; 
	private String gitPassword;
	private SendTimeout sendTimeout;
		
	public KalimaClientCallBack(Client client, String gitUser, String gitPassword) {
		this.client = client;
		this.node = client.getNode() ; 
		this.logger = node.getLogger();
		contractManager = new ContractManager(logger);
		this.gitUser = gitUser;
		this.gitPassword = gitPassword;
		sendTimeout = new SendTimeout(client.getClone().getClonePreferences().getLoadConfig().getSendTimeout(), logger, node);
	}

	//isServer data received by a nioServer if true
	@Override
	public void putData(SocketChannel ch, KMessage msg) {
		KMsg kMsg = KMsg.setMessage(msg);
		if(kMsg.getType()!=KMsg.ADMIN) {
			sendTimeout.remove(kMsg);
			client.getClone().set(kMsg.getCachePath(), kMsg, true, false);
			System.out.println("putData cachePath=" + kMsg.getCachePath() + " key=" + kMsg.getKey() + " body=" + new String(kMsg.getBody()));
		}
	}

	@Override
	public void onConnectionChanged(int status, NioClient nioClient) {
		logger.log_srvMsg("ExampleClientNode", "KalimaClientCallBack", Logger.DEBUG, "onConnectionChanged status=" + status);
		client.getClone().onConnectedChange( (status==Node.CLIENT_STATUS_CONNECTED) ? new AtomicBoolean(true) : new AtomicBoolean(false), nioClient, false);
	}

	@Override
	public void putRequestData(SocketChannel ch, KMessage msg) {}

	@Override
	public void onNewVersion(int majver, int minver) {}

	//If we want to use a smart contract, check for any new data on the memcache and execute a smartcontract if there is
	@Override
	public void onNewCache(String cachePath) {
		if(gitUser != null && gitPassword != null) client.getClone().addListnerForUpdate(new SmartContractCallback(cachePath, client, contractManager, gitUser, gitPassword));				
	}

	@Override
	public void onCacheSynchronized(String cachePath) {
		
	}

	@Override
	public void send(KMessage arg0) {
		sendTimeout.put(KMsg.setMessage(arg0));
	}
}