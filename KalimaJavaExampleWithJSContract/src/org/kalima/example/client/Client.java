package org.kalima.example.client;
import java.io.IOException;
import java.util.Map;
import java.util.Scanner;

import org.kalima.cache.lib.Clone;
import org.kalima.cache.lib.ClonePreferences;
import org.kalima.cache.lib.KMsg;
import org.kalima.cache.lib.KalimaNode;
import org.kalima.kalimamq.message.KMessage;
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
			int choice = Menu(scanner);
			initComponents();
			
			Thread.sleep(2000);
			System.out.println("GO");
			if(choice == 1)
				send10msg();
			else if (choice == 2)
				sendModulableMessage(scanner);
			scanner.close();
		} catch (Exception e) {
			logger.log_srvMsg("ExampleClientNode", "Client", Logger.ERR, e);
		}
		System.exit(0);
	}

	public void rmCache(String cachePath) throws InterruptedException {
		for(Map.Entry<String, KMessage> entry : clone.getMemCache(cachePath).getKvmap().entrySet()) {
			KMsg msg = KMsg.setMessage(entry.getValue());
			clone.remove(cachePath, msg.getKey());
		}
	}
	
	public int Menu(Scanner scanner){
		System.out.println("Do you want use Smart Contracts ? (Y/n)");
		String resp = scanner.nextLine();
		if(resp.equalsIgnoreCase("Y")) {
			System.out.println("Enter git username: ");
			gitUser = scanner.nextLine();
			System.out.println("Enter git password: ");
			gitPassword = scanner.nextLine();
		}
		System.out.println("What example do you want to use ?");
		System.out.println(" - Send 10 messages to /sensors (with ttl 10) : 1");
		System.out.println(" - Send/Delete 1 message of your choice : 2");
		int output = 0;
		while(output == 0) {
			String choice = scanner.nextLine();
			if(choice.equalsIgnoreCase("1"))
					output = 1;
			if(choice.equalsIgnoreCase("2"))
				output = 2;
			if(output == 0) {
				System.out.println("Invalid choice. Try Again");
			}
		}
		return output;
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
	
	public void send10msg() {
		try {
			// Here we make 10 transactions with body from 95 to 105 in cache path "/sensors", with key "keyx"
			// new KProps("10") set the ttl (time to live) to 10 seconds. So, the record will be automatically deleted in memCaches after 10 second
			// This is what you see when "putData cachePath=/sensors key=key0 body= " is printed
			// But of course, all transactions are still present in blockchain
			for(int i=0 ; i<10 ; i++) {
				String body = String.valueOf(95 + i);
				clone.put("/sensors", "key" + i, body.getBytes(), 10);
				Thread.sleep(1000);
			}
			Thread.sleep(10000);
		} catch (Exception e) {
			logger.log_srvMsg("ExampleClientNode", "Client", Logger.ERR, e);
		}
	}
	
	public void sendModulableMessage(Scanner scanner) {
		String choice = "";
		while(!choice.equalsIgnoreCase("a") && !choice.equalsIgnoreCase("d")) {
			System.out.println("Do you want to add (a) or delete (d) ?");
			choice = scanner.nextLine();
		}
		System.out.println("Type the cachePath you want to interact with :");
		String cachePath = scanner.nextLine();
		System.out.println("Type the key of your choice :");
		String key = scanner.nextLine();
		String value = "";
		if(choice.equalsIgnoreCase("a")) {
			System.out.println("Type the value of your choice :");
			value = scanner.nextLine();
			System.out.println("[key : " + key + " / value : " + value + "] added to cachePath : " + cachePath);
		}
		if(choice.equalsIgnoreCase("d")) {
			System.out.println("[key : " + key + "] deleted from cachePath : " + cachePath);
		}
		try {
			clone.put(cachePath, key, value.getBytes());
		} catch (Exception e) {
			logger.log_srvMsg("ExampleClientNode", "Client", Logger.ERR, e);
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
