package org.kalima.example.client;
import java.io.IOException;
import java.sql.Timestamp;
import java.util.Arrays;
import java.util.Map;
import java.util.Random;
import java.util.Scanner;

import org.kalima.cache.lib.Clone;
import org.kalima.cache.lib.ClonePreferences;
import org.kalima.cache.lib.KMsg;
import org.kalima.cache.lib.KProps;
import org.kalima.cache.lib.KalimaNode;
import org.kalima.dbmodel.Person;
import org.kalima.dbmodel.Thing;
import org.kalima.kalimamq.crypto.KKeyStore;
import org.kalima.kalimamq.message.KMessage;
import org.kalima.kalimamq.nodelib.KCache;
import org.kalima.kalimamq.nodelib.Node;
import org.kalima.util.Logger;

public class Client implements KalimaNode {

	private Node node;
	private Clone clone;
	private Logger logger;
	private KalimaClientCallBack clientCallBack;
	private ClonePreferences clonePreferences;
	private String gitUser;
	private String gitPassword;

	public Client(String[] args) {
		clonePreferences = new ClonePreferences(args[0]);
		logger = clonePreferences.getLoadConfig().getLogger();
	}

	public void run() {
		try {
			Scanner scanner = new Scanner(System.in);
			System.out.println("Do you want use Smart Contracts ? (Y/n)");
			String resp = scanner.nextLine();
			if(resp.equalsIgnoreCase("Y")) {
				System.out.println("Enter git username: ");
				gitUser = scanner.nextLine();
				System.out.println("Enter git password: ");
				gitPassword = scanner.nextLine();
			}
			scanner.close();
			
			initComponents();
			Thread.sleep(2000);
			System.out.println("GO");

			// Here we make 10 transactions with body "hello x" in cache path "/sensors", with key "keyx"
			// new KProps("10") set the ttl (time to live) to 10 seconds. So, the record will be automatically deleted in memCaches after 10 second
			// But of course, all transactions are still present in blockchain
			for(int i=0 ; i<10 ; i++) {
				String body = String.valueOf(21 + i);
				KMsg kMsg = new KMsg(0);				
				node.sendToNotaryNodes(kMsg.getMessage(node.getDevID(), KMessage.PUB, "/sensors", "key" + i, body.getBytes(), new KProps("10")));
				Thread.sleep(1000);
			}

		} catch (Exception e) {
			logger.log_srvMsg("ExampleClientNode", "Client", Logger.ERR, e);
		}
	}

	public void rmCache(String cachePath) throws InterruptedException {
		for(Map.Entry<String, KMessage> entry : clone.getMemCache(cachePath).getKvmap().entrySet()) {
			KMsg msg = KMsg.setMessage(entry.getValue());
			KMsg kMsg = new KMsg(0);
			node.sendToNotaryNodes(kMsg.getMessage(node.getDevID(), KMsg.PUB, cachePath, msg.getKey(), "".getBytes(), new KProps("-1")));
		}
	}

	public void initComponents(){
		node = new Node(clonePreferences.getLoadConfig());
		clone = new Clone(clonePreferences, node);

		clientCallBack = new KalimaClientCallBack(this, gitUser, gitPassword);

		try {
			node.connect(null, clientCallBack);
		} catch (IOException e) {
			logger.log_srvMsg("ExampleClientNode", "Client", Logger.ERR, "initComponents initNode failed : " + e.getMessage());
		}
	}

	public static void main(String[] args) {
		new Client(args).run();
	}

	public Node getNode() {
		return node;
	}

	@Override
	public Logger getLogger() {
		return logger;
	}

	@Override
	public Clone getClone() {
		return clone;
	}
}
