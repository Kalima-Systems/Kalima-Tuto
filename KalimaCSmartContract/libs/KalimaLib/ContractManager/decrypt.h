#ifndef DECRYPT_H
#define DECRYPT_H

/**
 * @file decrypt.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Decrypt a crypted file and checks file signature
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../KalimaCUtil/aes.h"
#include "../KalimaCUtil/BytesArray.h"
#include "../KalimaCUtil/openssl/include/sha.h"

/**
 * @brief Decrypt Aes crypted file
 * 
 * @param path File's path
 * @param aesKey Base64 encoded aes key
 * @param aesIV Base64 encoded aes IV
 * @return Decrypted file's content
 */
unsigned char*decrypt_file(char*path,char*aesKey,char*aesIV);

/**
 * @brief Checks if signature from BlockChain is the same as locally calculated file's signature
 * 
 * @param signature Signature from BlockChain
 * @param path File's path
 * @return 1 -- Right signature ; 0 -- Wrong signature
 */
int check_signature_SHA256(char*signature, char*path);


#endif