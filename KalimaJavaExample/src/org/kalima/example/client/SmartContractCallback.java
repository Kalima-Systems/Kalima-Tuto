package org.kalima.example.client;


import java.io.IOException;
import java.security.NoSuchAlgorithmException;

import org.kalima.cache.lib.KMsg;
import org.kalima.contractManager.ContractManager;
import org.kalima.kalimamq.message.KMessage;
import org.kalima.kalimamq.nodelib.MemCacheCallback;
import org.kalima.util.Logger;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

public class SmartContractCallback implements MemCacheCallback {

	private String GIT_SERVER = "http://95.111.241.13:3000/";
	private String GIT_HOST = "andre.legendre/";
	private String cachePath;
	private Logger logger;
	private ContractManager contractManager;
	private Client client;
	private Gson gson = new GsonBuilder().setDateFormat("MMM dd, yyyy h:mm:ss a").create();
	private String gitUser;
	private String gitPassword;

	public SmartContractCallback(String cachePath, Client client, ContractManager contractManager, String gitUser, String password) {
		super();
		this.cachePath = cachePath;
		this.logger = client.getLogger();
		this.contractManager = contractManager;
		this.client = client;
		this.gitUser = gitUser;
		this.gitPassword = password;
	}

	@Override
	public String getCachePath() {
		return cachePath;
	}

	@Override
	public void onCacheDeleted() {}

	@Override
	public void onConnectionChanged(int status) {}

	@Override
	public void putData(String key, KMessage msg) {
		KMsg kMsg = KMsg.setMessage(msg);
		if(cachePath.contentEquals("/Kalima_Scripts")) {
			handleScripts(kMsg);
		}
		runScript(kMsg);
	}

	private void handleScripts(KMsg kMsg) {
		try {
			contractManager.loadContract(GIT_SERVER + GIT_HOST, gitUser, gitPassword, kMsg.getKey(), kMsg.getBody());
		} catch (NoSuchAlgorithmException | IOException e) {
			logger.log_srvMsg("ExampleClientNode", "TableCallback", Logger.ERR, e);
		}
	}

	//Smart Contract execution example
	private void runScript(KMsg kMsg) {
		String scriptPath = logger.getBasePath() + "/git/KalimaContractsTuto" + kMsg.getCachePath() + ".js";
		try {
			String result = (String) contractManager.runFunction(scriptPath, "main", logger, kMsg, client.getClone(), client.getNode());
			logger.log_srvMsg("ExampleClientNode", "TableCallback", Logger.INFO, "script result=" + result);
		} catch (Exception e) {
			logger.log_srvMsg("ExampleClientNode", "TableCallback", Logger.ERR, e);
		}			
	}

	@Override
	public void removeData(String key) {
		if(cachePath.equals("/Kalima_Scripts")) {
			contractManager.removeContract(key);
		}
	}

	@Override
	public void setCachePath(String id) {}
}