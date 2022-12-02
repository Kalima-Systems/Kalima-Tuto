package org.kalima.smartcontractnode;

import java.rmi.RemoteException;

import org.kalima.cache.lib.KMsg;
import org.kalima.contractManager.UnknownContractException;
import org.kalima.kalimamq.message.KMessage;
import org.kalima.kalimamq.nodelib.MemCacheCallback;
import org.kalima.util.Logger;

public class CacheCallback implements MemCacheCallback {

	private String cachePath;
	private Logger logger;
	private Client client;

	public CacheCallback(String cachePath, Client client) {
		super();
		this.cachePath = cachePath;
		this.logger = client.getLogger();
		this.client = client;
	}

	@Override
	public String getAddress() {
		return cachePath;
	}

	@Override
	public void putData(KMessage msg) {
		KMsg kMsg = KMsg.setMessage(msg);
		try {
			if(client.getClientCallBack().getContractManager() != null) {
				if(kMsg.getAddress().equals("/Kalima_Scripts")) {
					client.getClientCallBack().getContractManager().downloadContract(kMsg.getProps().getProps());
				} else {
					client.getClientCallBack().getContractManager().runFunction(kMsg.getAddress().replaceFirst("/", "") + ".js", "main", msg, client.getClone(), logger);	
				}	
			}
		} catch (UnknownContractException e) {
		} catch (NoSuchMethodException e) {
			logger.log_srvMsg("SmartContractNode", "CacheCallback", Logger.ERR, "no main method in " + kMsg.getAddress() + ".js");
			logger.log_srvMsg("SmartContractNode", "CacheCallback", Logger.ERR, e);
		} catch (RemoteException e) {
			logger.log_srvMsg("SmartContractNode", "CacheCallback", Logger.ERR, e);
		}
	}

	@Override
	public void removeData(KMessage msg) {}
}