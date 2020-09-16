package org.kalima.example.client;


import java.io.IOException;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.Map;

import javax.script.SimpleBindings;

import org.kalima.cache.lib.Clone;
import org.kalima.cache.lib.KMsg;
import org.kalima.contractManager.ContractHousing;
import org.kalima.contractManager.ContractManager;
import org.kalima.dbmodel.Auth;
import org.kalima.kalimamq.message.KMessage;
import org.kalima.kalimamq.nodelib.MemCacheCallback;
import org.kalima.util.Logger;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

public class SmartContractCallback implements MemCacheCallback {

	private final String GIT_USERNAME = "user";
	private final String GIT_URL = "https://github.com/Kalima-Systems/";
	private String cachePath;
	private Logger logger;
	private ContractManager contractManager;
	private Client client;
	private Gson gson = new GsonBuilder().setDateFormat("MMM dd, yyyy h:mm:ss a").create();
	
	public SmartContractCallback(String cachePath, Client client, ContractManager contractManager) {
		super();
		this.cachePath = cachePath;
		this.logger = client.getLogger();
		this.contractManager = contractManager;
		this.client = client;
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
		} else if(cachePath.equals("/sensors")) {
			handleSensors(kMsg);
		} else if(cachePath.equals("/Kalima_Password") && kMsg.getKey().equals("git/" + GIT_USERNAME)) {
			handlePassword(kMsg);
		}
	}
	
	private void handleScripts(KMsg kMsg) {
		try {
			KMsg passwordMsg;
			if((passwordMsg=client.getClone().get("/Kalima_Password", "git/" + GIT_USERNAME)) != null) {
				String password = gson.fromJson(new String(passwordMsg.getBody()), Auth.class).getPassword();
				contractManager.loadContract(GIT_URL, GIT_USERNAME, password, kMsg.getKey(), kMsg.getBody());
			}
		} catch (NoSuchAlgorithmException | IOException e) {
			logger.log_srvMsg("ExampleClientNode", "TableCallback", Logger.ERR, e);
		}
	}
	
	private void handleSensors(KMsg kMsg) {
		String scriptPath = logger.getBasePath() + "/git/Kalima-Tuto/etc/scripts/reverse_string.js";
		ContractHousing contractHousing = this.contractManager.getContractHousing(scriptPath);
		if(contractHousing != null) {
			SimpleBindings bindings = contractHousing.getBindings();
			bindings.put("kMsg", kMsg);
			bindings.put("logger", logger);
			try {
				String result = (String) contractManager.runScript(scriptPath);
				logger.log_srvMsg("ExampleClientNode", "TableCallback", Logger.INFO, "script result=" + result);
			} catch (Exception e) {
				logger.log_srvMsg("ExampleClientNode", "TableCallback", Logger.ERR, e);
			}	
		}
	}
	
	private void handlePassword(KMsg kMsg) {
		for(Map.Entry<String, KMessage> entry : client.getClone().getMemCache("/Kalima_Scripts").getKvmap().entrySet()) {
			KMsg scriptMsg = KMsg.setMessage(entry.getValue());
			try {
				String password = gson.fromJson(new String(kMsg.getBody()), Auth.class).getPassword();
				contractManager.loadContract(GIT_URL, GIT_USERNAME, password, scriptMsg.getKey(), scriptMsg.getBody());
			} catch (NoSuchAlgorithmException | IOException e) {
				logger.log_srvMsg("ExampleClientNode", "TableCallback", Logger.ERR, e);
			}
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