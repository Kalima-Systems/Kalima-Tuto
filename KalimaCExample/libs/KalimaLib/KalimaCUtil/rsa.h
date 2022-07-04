#ifndef RSA_H
#define RSA_H

#include "openssl/include/bn.h"
#include "openssl/include/rsa.h"
#include "openssl/include/pem.h"
#include "openssl/include/bio.h"
#include "openssl/include/ssl.h"
#include "openssl/include/evp.h"
#include "openssl/include/err.h"
#include <stdio.h>
#include <stdint.h>

void generate_pems(char* public, int public_size, char* private, int private_size);

uint16_t get_key(FILE* pem_file, unsigned char* key);

RSA* load_key_RSA(FILE* pem_file, int32_t pub);
RSA* create_RSA(unsigned char * key, int32_t key_size, int32_t pub);
int32_t encrypt_with_public(unsigned char * data, int32_t data_len, unsigned char *encrypted, FILE* pem_file);
int32_t decrypt_with_public(unsigned char * data, int32_t data_len, unsigned char *decrypted, FILE* pem_file);

int32_t encrypt_with_private(unsigned char * data, int32_t data_len, unsigned char *encrypted, FILE* pem_file);
int32_t decrypt_with_private(unsigned char * data, int32_t data_len, unsigned char *decrypted, FILE* pem_file);

#endif
