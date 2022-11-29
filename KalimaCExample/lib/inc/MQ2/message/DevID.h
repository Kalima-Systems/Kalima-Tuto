#ifndef DevID_h
#define DevID_h

/**
 * @file DevID.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Get MACAddress
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <ifaddrs.h>

/**
 * @brief MAC Address size (6 uint8_t)
 * 
 */
#define MACAddr_size 6

/**
 * @brief Set a random MAC Address
 * 
 * @param macAddr Output MAC Address
 */
void random_MACAddress(char macAddr[MACAddr_size]);
/**
 * @brief Get MAC Address from system
 * 
 * @param macAddr Output MAC Address
 */
void get_MACAddress(char macAddr[MACAddr_size]);

#endif