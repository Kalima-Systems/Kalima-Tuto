package org.kalima.java.example;

import java.util.InputMismatchException;
import java.util.Map;
import java.util.Scanner;

import org.kalima.cache.lib.Clone;
import org.kalima.cache.lib.ClonePreferences;
import org.kalima.cache.lib.KMsg;
import org.kalima.cache.lib.MemCache;
import org.kalima.kalimamq.message.KMessage;
import org.kalima.util.Logger;

public class Client {

	private Clone clone;
	private Logger logger;

	public static void main(String args[]) {
		new Client(args[0]);
	}

	public Client(String configFilePath) {
		ClonePreferences clonePreferences = new ClonePreferences(configFilePath);
		logger = clonePreferences.getLoadConfig().getLogger();
		clone = new Clone(clonePreferences);
		KalimaClientCallback kalimaClientCallback = new KalimaClientCallback(clone);
		clone.connect(kalimaClientCallback);

		Scanner scanner = new Scanner(System.in);
		boolean stop = false;
		while(!stop) {
			menu();
			String choice = scanner.next();
			switch (choice) {
			case "1":
				printAddresses();
				break;

			case "2":
				System.out.println("Enter address:");
				printContentOfAddress(scanner.next());
				break;

			case "3":
				printContentOfAllAddresses();
				break;

			case "4":
				System.out.println("Enter temperature (int):");
				try {
					putTemperature(scanner.nextInt());	
				} catch (InputMismatchException e) {
					System.out.println("You must enter an integer");
					scanner.nextLine();
				}
				break;

			case "5":
				stop = true;
				break;

			default:
				break;
			}
		}
		scanner.close();
		System.exit(0);
	}

	public void menu() {
		System.out.println("1- print all addresses");
		System.out.println("2- print content of address");
		System.out.println("3- print content of all addresses");
		System.out.println("3- print content of all addresses");
		System.out.println("5- close");
	}

	private void printAddresses() {
		for(String addr : clone.getAddresses()) {
			System.out.println(addr);
		}
	}

	private void printContentOfAddress(String address) {
		MemCache memCache = (MemCache) clone.getMemCache(address);
		if(memCache == null) {
			System.out.println("Address " + address + " not found");
			return;
		}

		for(Map.Entry<String, KMessage> entry : memCache.getKvmap().entrySet()) {
			KMsg kMsg = KMsg.setMessage(entry.getValue());
			System.out.println("KEY=" + entry.getKey() + " BODY=" + new String(kMsg.getBody()));
		}
	}

	private void printContentOfAllAddresses() {
		for(String addr : clone.getAddresses()) {
			System.out.println("*** " + addr + " ***");
			printContentOfAddress(addr);
			System.out.println();
		}
	}

	private void putTemperature(int temperature) {
		clone.put("/sensors", "temperature", String.valueOf(temperature).getBytes());
	}
	 
}
