/**
	Auteur : Jérôme Delaire
	Date : 09/09/2020
	Script de démo pour inverser un string contenu dans un KMsg
**/
load("nashorn:mozilla_compat.js");
importPackage(Packages.java.io);
importPackage(Packages.java.lang);
importPackage(Packages.java.util);
importPackage(org.kalima.kalimamq.nodelib);
importPackage(org.kalima.util);

var JString = Java.type("java.lang.String");

function main(kMsg, clone, logger) {
	var body = new JString(kMsg.getBody());
	logger.log_srvMsg("Scripts", "fire.js", Logger.INFO, "key=" + kMsg.getKey() + "body=" + body);
}
