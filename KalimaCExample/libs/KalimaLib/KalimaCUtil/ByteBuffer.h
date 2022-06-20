#ifndef _BYTEBUFFER_H_
#define _BYTEBUFFER_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

// Default number of bytes to allocate in the backing buffer if no size is provided
#define BB_DEFAULT_SIZE 4096

typedef struct byte_buffer_t {
    uint32_t pos; // Read/Write position
    bool wrapped; // True if this byte buffer is a wrapping buf
    size_t len; // Length of buf array
    uint8_t *buf;
} byte_buffer;

// Memory allocation functions
byte_buffer *bb_new_wrap(uint8_t *buf, size_t len);
byte_buffer *bb_new(size_t len);

// Utility
void bb_clear(byte_buffer *bb);
void bb_print_ascii(byte_buffer *bb);
void bb_print_hex(byte_buffer *bb);

// Read functions
uint8_t bb_get(byte_buffer *bb);
void bb_get_bytes_in(byte_buffer *bb, uint8_t *dest, size_t len);
uint8_t *bb_get_bytes(byte_buffer *bb, size_t len);
int64_t bb_get_long(byte_buffer *bb);
int64_t bb_get_long_at(byte_buffer *bb, uint32_t index);

// Put functions (simply drop bytes until there is no more room)
void bb_put_long(byte_buffer *bb, int64_t value);

#endif