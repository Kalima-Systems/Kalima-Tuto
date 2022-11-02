#ifndef BYTESARRAY_H
#define BYTESARRAY_H

/**
 * @file BytesArray.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Usefull functions that can be used anytime
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "openssl/include/bio.h"
#include "openssl/include/evp.h"

/**
 * @brief Define long format depending on architecture
 * 
 */
# if __x86_64__
#  define LONG_A	"ld"
# else
#  define LONG_A	"lld"
# endif

/**
 * @brief Get number of "c" character in string
 * 
 * @param string Char array to analyze
 * @param c Character to look for
 * @return Number of occurence
 */
int get_nb_occurence(char* string, char c);
/**
 * @brief Get part of string after last occurence of a character
 * @details Can be usefull to get file name from full path
 * 
 * @param string Char array to analyze
 * @param c Character to look for
 * @param nb_of_c Number of occurence of "c"
 * @return The part of the string after last occurence 
 */
char* get_after_last_occurence(char* string, char c, int nb_of_c);
/**
 * @brief Transform a hexadecimal array to a char array
 * 
 * @param src Hex array
 * @param out Output char array
 * @param size size of the hex array
 */
void hex_to_charArray(unsigned char* src, unsigned char* out, int32_t size);
/**
 * @brief Hexadecimal to string
 * 
 * @param hex Hex array
 * @param len Hex array size
 * @return String
 */
char* hex2str(unsigned char *hex,int len);
/**
 * @brief Remove character from string
 * 
 * @param key Input string
 * @param key_size Input string size
 * @param toRemove Character to remove
 * @return uint16_t 
 */
uint16_t remove_from_key(unsigned char * key, uint16_t key_size, const char toRemove);
/**
 * @brief Calculates the length of a decoded base64 string
 * @details Used in Base64Decode()
 * 
 * @param b64input Base64 string
 * @param len Base64 string size
 * @return Decoded length 
 */
int32_t calcDecodeLength(const unsigned char* b64input, int32_t len);
/**
 * @brief Decode a base64 encoded string
 * 
 * @param b64message Base64 string
 * @param b64message_size Base64 string size
 * @param buffer Decoded string
 * @return Decoded string size
 */
int32_t Base64Decode(unsigned char* b64message, int32_t b64message_size, unsigned char** buffer);
/**
 * @brief Encode a base64 string
 * 
 * @param message String
 * @param message_size String size
 * @param buffer Base64 encoded string
 * @return Encoded size
 */
int32_t Base64Encode(const unsigned char* message, int32_t message_size, unsigned char** buffer);
/**
 * @brief Get number of characters in an integer (ex : 1026 = 4)
 * 
 * @param value Integer
 * @return Number of characters
 */
uint8_t get_int_len (int64_t value);
/**
 * @brief Equivalent of math.h ceil
 * 
 * @param a a
 * @param b b
 * @return int32_t 
 */
int32_t calculate_ceil(int a, int b);
/**
 * @brief Copy data into secured string
 * 
 * @param data Data to copy
 * @param data_size Data size
 * @param string Output string
 */
void set_String(void* data, uint16_t data_size, void** string);

/**
 * @brief Strncmp that automaticaly takes highest length
 * 
 * @param str1 String 1
 * @param str2 String 2
 * @return Same as strncmp
 */
int string_compare(char* str1, char* str2);

#endif
