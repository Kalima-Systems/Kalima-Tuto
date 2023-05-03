#ifndef OPENSSLUTIL_H
#define OPENSSLUTIL_H

#include "openssl/bio.h"
#include "openssl/evp.h"
#include "BytesArray.h"

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

#endif