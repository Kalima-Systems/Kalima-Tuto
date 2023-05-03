#ifndef BUFFERCHAIN_H
#define BUFFERCHAIN_H

/**
 * @file BufferChain.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief String acting as a buffer where you can add and delete data
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>

/**
 * @brief Max size of a message to send to BlockChain
 * 
 */
#define SEND_SIZE 8000

/**
 * @brief Max size of a message received from socket read
 * 
 */
#define BUFFER_SIZE 16000

/**
 * @brief Max size of Buffer
 * 
 */
#define MAX_BUFFER_SIZE 64000

/**
 * @brief Buffer structure
 * @details Structure containing a static uint8_t array with MAX_BUFFER_SIZE as size and the size of the actual data put in the buffer
 */
typedef struct Buffer Buffer;
struct Buffer{
    uint8_t data[MAX_BUFFER_SIZE]; /**< Static uint8_t array with MAX_BUFFER_SIZE as size */
    uint16_t BufferSize; /**< Size of the actual data put in the buffer */
};

/**
 * @brief Initialize an empty Buffer
 * 
 * @return On success : Pointer to Buffer @n
 *         On failure : NULL
 */
Buffer *create_Buffer();

/**
 * @brief Add data to buffer
 * 
 * @param buf Buffer structure
 * @param data data to add to the buffer
 * @param data_size size of the data to add
 * @return On success : 1 @n
 *         On failure : -1
 */
int8_t Buffer_add(Buffer *buf, void* data, uint16_t data_size);

/**
 * @brief Delete data_size characters from the start of the buffer
 * 
 * @param buf Buffer structure
 * @param data_size size of the data to delete (at the start of the buffer)
 */
void Buffer_delete_data(Buffer *buf, uint16_t data_size);

/**
 * @brief Free a Buffer
 * 
 * @param buf Pointer to Buffer
 */
void Buffer_free(Buffer *buf);

#endif