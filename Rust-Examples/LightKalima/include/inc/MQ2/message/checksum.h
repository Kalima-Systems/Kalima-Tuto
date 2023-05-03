#ifndef DEF_LIBCRC_CHECKSUM_H
#define DEF_LIBCRC_CHECKSUM_H

/**
 * @file checksum.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Calculate CRC for KMsg
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Calculates CRC_64_ECMA for given input
 * 
 * @param input_str Input string
 * @param num_bytes Input size
 * @return CRC 
 */
uint64_t crc_64_ecma(uint8_t *input_str, size_t num_bytes);
/**
 * @brief Updates CRC
 * 
 * @param crc CRC
 * @param c 
 * @return Updates CRC
 */
uint64_t update_crc_64_ecma(uint64_t crc, unsigned char c);

#endif  // DEF_LIBCRC_CHECKSUM_H