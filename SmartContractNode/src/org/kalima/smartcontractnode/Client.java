package org.kalima.smartcontractnode;
import org.kalima.cache.lib.Clone;
import org.kalima.cache.lib.ClonePreferences;
import org.kalima.util.Logger;

public class Client {

	private Clone clone;
	private Logger logger;
	private KalimaClientCallBack clientCallBack;
	private ClonePreferences clonePreferences; 

	public Client(String[] args) {
		clonePreferences = new ClonePreferences(args[0]);
		logger = clonePreferences.getLoadConfig().getLogger();
		initComponents();
	}

	public void initComponents(){
		clone = new Clone(clonePreferences);
		clientCallBack = new KalimaClientCallBack(this);
		clone.connect(clientCallBack);
	}

	public static void main(String[] args) {
		new Client(args);
	}
	
	public Logger getLogger() {
		return logger;
	}

	public Clone getClone() {
		return clone;
	}

	public ClonePreferences getClonePreferences() {
		return clonePreferences;
	}

	public KalimaClientCallBack getClientCallBack() {
		return clientCallBack;
	}

	public String getContractCache() {
		return "/Kalima_Contracts/Kalima";
	}
}
