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

/**
 * @brief Define long format depending on architecture
 * 
 */
# if __x86_64__
#  define LONG_A	"ld"
# else
#  define LONG_A	"lld"
# endif

void mkdirr(const char *dir);

/**
 * @brief String to hexadecimal (ex "132" -> "313332")
 * 
 * @param str String to turn into hexa
 * @param len String size
 * @return Hexa string
 */
char* str2hex(unsigned char *str,int len);
/**
 * @brief Get number of characters in an integer (ex : 1026 = 4)
 * 
 * @param value Integer
 * @return Number of characters
 */
uint8_t get_int_len (int64_t value);
/**
 * @brief Copy data into secured string
 * 
 * @param data Data to copy
 * @param data_size Data size
 * @param string Output string
 * @return On success : 1 @n
 *         On failure : -1
 */
int8_t set_String(void* data, uint16_t data_size, void** string);

/**
 * @brief Strncmp that automaticaly takes highest length
 * 
 * @param str1 String 1
 * @param str2 String 2
 * @return Same as strncmp
 */
int string_compare(char* str1, char* str2);

#endif
