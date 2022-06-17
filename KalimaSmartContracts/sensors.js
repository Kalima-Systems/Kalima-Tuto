/**
	Auteur : Jérôme Delaire
	Date : 09/03/2021
	Script de démo pour créer une transaction sur Kalima
**/
load("nashorn:mozilla_compat.js");
importPackage(Packages.java.io);
importPackage(Packages.java.lang);
importPackage(Packages.java.util);
importPackage(org.kalima.kalimamq.message);
importPackage(org.kalima.cache.lib);
importPackage(org.kalima.util);

var JString = Java.type("java.lang.String");

function main(kMsg, clone, logger) {
	
	if(!kMsg.getKey().equals("temperature2")) return;
	
	var body = new JString(kMsg.getBody());
	var temperature = parseInt(body, 10);
	if(temperature == null)
		return "NOK";

	if(temperature >= 100) {
		clone.put("/alarms/fire", kMsg.getKey(), ("Temperature too high: " + temperature + " °C").getBytes());
	}
}
