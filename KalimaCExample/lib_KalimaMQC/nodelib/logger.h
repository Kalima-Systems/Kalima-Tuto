#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMERGE 0
#define ALERT 10
#define CRIT 20
#define ERR 30
#define WARNING 40
#define NOTICE 50
#define INFO 60
#define DEBUG 70
#define VERB 80

void log_srvMsg(char* path, char* service_Name, char* log_Name, int log_lvl, char* message);

#endif