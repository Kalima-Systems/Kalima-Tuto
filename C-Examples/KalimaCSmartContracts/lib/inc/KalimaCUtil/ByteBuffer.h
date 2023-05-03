#ifndef _BYTEBUFFER_H_
#define _BYTEBUFFER_H_

/**
 * @file ByteBuffer.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Functions to transform longs to strings and strings to longs
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

/**
 * @brief Default number of bytes to allocate in the backing buffer if no size is provided
 * 
 */
#define BB_DEFAULT_SIZE 4096

/**
 * @brief byte_buffer_t structure
 * @details Structure used to do the transition
 */
typedef struct byte_buffer_t {
    uint32_t pos; /**< Read/Write position */
    bool wrapped; /**< True if this byte buffer is a wrapping buf */
    size_t len; /**< Length of buf array */
    uint8_t *buf; /**< Buf array */
} byte_buffer;

/**
 * @brief Memory allocation function with data
 * 
 * @param buf Data to put in array
 * @param len Size of the data
 * @return pointer to byte_buffer 
 */
byte_buffer *bb_new_wrap(uint8_t *buf, size_t len);
/**
 * @brief Memory allocation function
 * 
 * @param len Size of the data that will be put later
 * @return Pointer to byte_buffer 
 */
byte_buffer *bb_new(size_t len);

/**
 * @brief Free a ByteBuffer
 * 
 * @param bb Pointer to ByteBuffer
 */
void bb_free(byte_buffer *bb);

/**
 * @brief Clear a byte_buffer
 * 
 * @param bb Pointer to byte_buffer
 */
void bb_clear(byte_buffer *bb);
/**
 * @brief Print a byte_buffer in ASCII format
 * 
 * @param bb Pointer to byte_buffer
 */
void bb_print_ascii(byte_buffer *bb);
/**
 * @brief Print a byte_buffer in hex format
 * 
 * @param bb Pointer to byte_buffer
 */
void bb_print_hex(byte_buffer *bb);

/**
 * @brief Get byte at pos (will increment pos)
 * 
 * @param bb Pointer to byte_buffer
 * @return byte at pos
 */
uint8_t bb_get(byte_buffer *bb);
/**
 * @brief Get byte array from byte_buffer and put it in dest array
 * 
 * @param bb Pointer to byte_buffer
 * @param dest destination byte array
 * @param len length of byte array
 */
void bb_get_bytes_in(byte_buffer *bb, uint8_t *dest, size_t len);
/**
 * @brief Get byte array from byte_buffer and return
 * 
 * @param bb Pointer to byte_buffer
 * @param len length of byte array
 * @return byte array 
 */
uint8_t *bb_get_bytes(byte_buffer *bb, size_t len);
/**
 * @brief Get long from byte_buffer
 * 
 * @param bb Pointer to byte_buffer
 * @return data in long format
 */
int64_t bb_get_long(byte_buffer *bb);
/**
 * @brief Get long from byte_buffer starting at index pos
 * 
 * @param bb Pointer to byte array
 * @param index index
 * @return data in long
 */
int64_t bb_get_long_at(byte_buffer *bb, uint32_t index);

/**
 * @brief Put long in byte_buffer as byte array
 * 
 * @param bb Pointer to byte_buffer
 * @param value long to put
 */
void bb_put_long(byte_buffer *bb, int64_t value);

#endif