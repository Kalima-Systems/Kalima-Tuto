/**
	Auteur : Jérôme Delaire
	Date : 09/03/2021
	Script de démo pour créer une transaction sur Kalima
**/
load("nashorn:mozilla_compat.js");
importPackage(Packages.java.io);
importPackage(Packages.java.lang);
importPackage(Packages.java.util);
importPackage(org.kalima.kalimamq.nodelib);
importPackage(org.kalima.kalimamq.message);
importPackage(org.kalima.cache.lib);
importPackage(org.kalima.util);

var JString = Java.type("java.lang.String");
var KMsg = Java.type("org.kalima.cache.lib.KMsg");
var KProps = Java.type("org.kalima.cache.lib.KProps");

function main(logger, kMsg, clone, node) {
	
	var body = new JString(kMsg.getBody());
	var value = parseInt(body, 10);
	if(value == null)
		return "NOK";

	if(value >= 100) {
		var kMsg1 = new KMsg(0);
		node.sendToNotaryNodes(kMsg1.getMessage(node.getDevID(), KMessage.PUB, "/alarms/fire", kMsg.getKey(), kMsg.getBody() , new KProps("-1")));
	}
	
	return "OK";
}