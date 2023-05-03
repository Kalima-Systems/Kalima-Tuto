#ifndef RSA_H
#define RSA_H

/**
 * @file rsa.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Usefull RSA functions using openssl library
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "openssl/bn.h"
#include "openssl/rsa.h"
#include "openssl/pem.h"
#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/evp.h"
#include "openssl/err.h"
#include <stdio.h>
#include <stdint.h>

/**
 * @brief Generate public and private .pem files
 * 
 * @param public Public.pem path
 * @param public_size Public.pem path size
 * @param private Private.pem path
 * @param private_size Private.pem size
 */
void generate_pems(char* public, int public_size, char* private, int private_size);

/**
 * @brief Get key from .pem file (with format)
 * 
 * @param pem_file Pem FILE
 * @param key Key read from FILE
 * @return Key size
 */
uint16_t get_key(FILE* pem_file, unsigned char* key);

/**
 * @brief Load key from .pem file
 * 
 * @param pem_file Pem FILE
 * @param pub If pub=1 : pem file is public.pem / if pub=0 : pem file is private.pem
 * @return Pointer to RSA
 */
RSA* load_key_RSA(FILE* pem_file, int32_t pub);

/**
 * @brief Encrypt data with public RSA key
 * 
 * @param data Data to encrypt
 * @param data_len Data length
 * @param encrypted Encrypted data
 * @param pem_file Pem FILE
 * @return Encrypted data size
 */
int32_t encrypt_with_public(unsigned char * data, int32_t data_len, unsigned char *encrypted, FILE* pem_file);
/**
 * @brief Decrypt data with public RSA key
 * 
 * @param data Data to decrypt
 * @param data_len Data length
 * @param encrypted Decrypted data
 * @param pem_file Pem FILE
 * @return DEcrypted data size
 */
int32_t decrypt_with_public(unsigned char * data, int32_t data_len, unsigned char *decrypted, FILE* pem_file);

/**
 * @brief Encrypt data with private RSA key
 * 
 * @param data Data to encrypt
 * @param data_len Data length
 * @param encrypted Encrypted data
 * @param pem_file Pem FILE
 * @return Encrypted data size
 */
int32_t encrypt_with_private(unsigned char * data, int32_t data_len, unsigned char *encrypted, FILE* pem_file);
/**
 * @brief Decrypt data with private RSA key
 * 
 * @param data Data to decrypt
 * @param data_len Data length
 * @param encrypted Decrypted data
 * @param pem_file Pem FILE
 * @return DEcrypted data size
 */
int32_t decrypt_with_private(unsigned char * data, int32_t data_len, unsigned char *decrypted, FILE* pem_file);

#endif
