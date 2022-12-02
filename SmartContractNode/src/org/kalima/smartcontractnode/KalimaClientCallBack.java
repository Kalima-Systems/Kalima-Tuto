package org.kalima.smartcontractnode;

import java.io.IOException;
import java.nio.channels.SocketChannel;
import java.util.Properties;

import org.kalima.cache.lib.KMsg;
import org.kalima.contractManager.ContractCallback;
import org.kalima.contractManager.ContractManager;
import org.kalima.kalimamq.message.KMessage;
import org.kalima.kalimamq.nodelib.ClientCallback;
import org.kalima.util.Logger;

public class KalimaClientCallBack implements ClientCallback {

	private Client client;
	private Logger logger ;
	private ContractManager contractManager;
	private boolean contractManagerRun = false;

	public KalimaClientCallBack(Client client) {
		this.client = client; 
		this.logger = client.getLogger();
	}

	@Override
	public void putRequestData(SocketChannel ch, KMessage msg) {}

	@Override
	public void onNewVersion(int majver, int minver) {}

	@Override
	public void onNewCache(String address) {
		client.getClone().addMemCacheCallback(new CacheCallback(address, client));
	}

	@Override
	public void onCacheSynchronized(String address) {
		if(address.equals("/Kalima_Scripts") && !contractManagerRun) {
			contractManagerRun = true;
			contractManager = new ContractManager(logger, logger.getBasePath(),  new ContractCallback() {

				@Override
				public Properties getContractInfos(String key) {
					System.out.println("get key " + key);
					KMsg contractInfosMsg = client.getClone().get("/Kalima_Scripts", key);
					if(contractInfosMsg == null) {
						System.out.println("contract infos not found for " + key);
						return null;
					}

					return contractInfosMsg.getProps().getProps();
				}
			});	
			for(KMessage msg : client.getClone().getMemCache(address).getKvmap().values()) {
				client.getClientCallBack().getContractManager().downloadContract(KMsg.setMessage(msg).getProps().getProps());
			}
		}
	}

	public ContractManager getContractManager() {
		return contractManager;
	}

	@Override
	public void onReject(SocketChannel arg0) {
		System.out.println("You are not authorized on this Blockchain.");	
		System.out.println("Please contact an administrator");
		System.exit(-1);
	}
}