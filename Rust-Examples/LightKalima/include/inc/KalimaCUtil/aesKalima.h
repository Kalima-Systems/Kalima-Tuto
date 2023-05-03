#ifndef _AES_H_
#define _AES_H_

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Encyrpt a msg for Kalima communication
 * 
 * @param msg msg to encrypt
 * @param size size of the msg to encrypt
 * @param key key used for encryption
 * @param iv IV used for encryption
 * @return encrypted msg size
 */
uint16_t encrypt_msg(uint8_t* msg, uint16_t size, uint8_t* key, uint8_t* iv);
/**
 * @brief Decrypt a msg for Kalima communication
 * 
 * @param msg msg to decrypt
 * @param size size of the msg to decrypt
 * @param key key used to decrypt
 * @param iv IV used to decrypt
 * @return decrypted msg size
 */
uint16_t decrypt_msg(uint8_t* msg, uint16_t size, uint8_t* key, uint8_t* iv);

#endif // _AES_H_