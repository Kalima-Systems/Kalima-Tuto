#ifndef BYTESARRAY_H
#define BYTESARRAY_H

#include <stdint.h>

# if __x86_64__
#  define LONG_A	"ld"
# else
#  define LONG_A	"lld"
# endif

void hex_to_charArray(unsigned char* src, unsigned char* out, int32_t size);
uint16_t remove_from_key(unsigned char * key, uint16_t key_size, const char toRemove);
int32_t calcDecodeLength(const unsigned char* b64input, int32_t len);
int32_t Base64Decode(unsigned char* b64message, int32_t b64message_size, unsigned char** buffer);
int32_t Base64Encode(const unsigned char* message, int32_t message_size, unsigned char** buffer);
uint8_t get_int_len (int64_t value);

#endif