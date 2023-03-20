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

#include <stdint.h>
#include "BytesArray.h"

/**
 * @brief MAC Address size (6 uint8_t)
 *
 */
#define MACAddr_size 6

unsigned char MacAddress[MACAddr_size];
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
 * @return On success : 1 @n
 *         On failure : -1
 */
#if __linux__
int8_t get_MACAddress(char macAddr[MACAddr_size]);
#elif __APPLE__
void get_MACAddress(unsigned char macAddr[MACAddr_size]);
#endif

/**
 * @brief Randomize maC address
 * 
 * @param macAddr MAC address
 */
void randomize_MAC(char* macAddr);

#endif