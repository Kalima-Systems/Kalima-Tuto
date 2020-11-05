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

function main(logger, kMsg) {
	var body = new JString(kMsg.getBody());
	var reverseString = "";
	logger.log_srvMsg("Scripts", "ReverseString", Logger.INFO, "body=" + body);

	for(i=body.length ; i>=0; i--) {
		reverseString += body.charAt(i);
	}
	logger.log_srvMsg("Scripts", "ReverseString", Logger.INFO, "reverseString=" + reverseString);

	return reverseString;
}
