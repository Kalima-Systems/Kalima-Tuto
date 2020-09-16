package org.kalima.example.client;
import java.io.IOException;
import java.sql.Timestamp;
import java.util.Arrays;
import java.util.Map;
import java.util.Random;

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
	private KalimaServerCallBack serverCallBack;
	private KalimaClientCallBack clientCallBack;
	private ClonePreferences clonePreferences;
	private byte[] devId ;

	public Client(String[] args) {
		clonePreferences = new ClonePreferences(args[0]);
		logger = clonePreferences.getLoadConfig().getLogger();
	}

	public void run() {
		try {
			initComponents();
			Thread.sleep(2000);
			System.out.println("GO");

			// Ici on envoit 10 messages "hello x" dans le channel "/sensors" avec l'id unique "key"
			// Comme l'id unique reste le meme, "hello 1" sera ecrase par "hello2" et ainsi de suite
			// Cependant toutes les valeurs persisteront dans l'historique
			// new KProps("10") place le ttl (time to live) a 10 seconde. ce qui signifie que le message sera supprime dans 10 secondes
			for(int i=0 ; i<10 ; i++) {
				String body = "hello" + i;
				KMsg kMsg = new KMsg(0);				
				node.sendToNotaryNodes(kMsg.getMessage(devId, KMessage.PUB, "/sensors", "key" + i, body.getBytes(), new KProps("10")));
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
			node.sendToNotaryNodes(kMsg.getMessage(devId, KMsg.PUB, cachePath, msg.getKey(), "".getBytes(), new KProps("-1")));
		}
	}

	public void initComponents(){
		byte[] key = new byte[] {
				(byte)0x20, (byte)0xf7, (byte)0xdf, (byte)0xe7,
				(byte)0x18, (byte)0x26, (byte)0x0b, (byte)0x85,
				(byte)0xff, (byte)0xc0, (byte)0x9d, (byte)0x54,
				(byte)0x28, (byte)0xff, (byte)0x10, (byte)0xe9
		};

		devId = KKeyStore.setDevId(clonePreferences.getLoadConfig().getFilesPath(), key, logger);

		node = new Node(clonePreferences.getLoadConfig());
		node.setDevID(devId);
		clone = new Clone(clonePreferences, node);

		serverCallBack = new KalimaServerCallBack();
		clientCallBack = new KalimaClientCallBack(this);

		try {
			node.connect(serverCallBack, clientCallBack);
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
