#ifndef LOGGER_H
#define LOGGER_H

/**
 * @file logger.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Create log files and print logs in them
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>

#define EMERGE 0
#define ALERT 10
#define CRIT 20
#define ERR 30
#define WARNING 40
#define NOTICE 50
#define INFO 60
#define DEBUG 70
#define VERB 80

/**
 * @brief Write logs
 * @details Will create log file if it doesn't already exist (format : service_Namelog_Name.date, ex : servicelog.221005)
 * 
 * @param path Log file path
 * @param service_Name Service Name (will be concatenated with log_Name for log file name)
 * @param log_Name Log Name (will be concatenated with service_Name for log file name)
 * @param log_lvl Log level (see defines)
 * @param message Message to add to logs
 */
void log_srvMsg(char* path, char* service_Name, char* log_Name, uint8_t log_lvl, char* message);

#endif