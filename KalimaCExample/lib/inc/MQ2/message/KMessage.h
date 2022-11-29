#ifndef KMESSAGE_H
#define KMESSAGE_H

/**
 * @file KMessage.h
 * @author André Legendre
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief KMessage
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdarg.h>
#include <stdint.h>
#include "Header.h"
#include "aesKalima.h"
#include "BytesArray.h"

/**
 * @brief KMessage structure
 * 
 */
typedef struct KMessage KMessage;
struct KMessage{
    struct Header *header; /**< Pointer to KMessage's Header */
	unsigned char** frames; /**< 2D array : 1 array for each frame */
};

/**
 * @brief Allocate a new KMessage
 * 
 * @return Pointer to KMessage
 */
struct KMessage* KMessage_new();
/**
 * @brief Create a KMessage
 * 
 * @param frames Every frames concatenated as a 1D array
 * @param nbFrames Number of frames
 * @param sizes Frames' sizes array
 * @return Pointer to KMessage 
 */
struct KMessage* create_KMessage(unsigned char* frames, int32_t nbFrames, int32_t* sizes);
/**
 * @brief Create a KMessage using va_list (crashes on 32bit systems)
 * 
 * @param nbFrames Number of frames
 * @param frame1 frame1's bytes
 * @param size1 frames1's size
 * @param ...  Same for every frame
 * @return Pointer to KMessage 
 */
struct KMessage* create_KMessage2(int32_t nbFrames, unsigned char* frame1, int32_t size1, ...);
/**
 * @brief Construct Kmessage's Header
 * 
 * @param kmessage Pointer to KMessage
 * @param nbFrames Number of frames
 * @param sizes KMessage's frames sizes
 */
void construct_Header(struct KMessage* kmessage, int32_t nbFrames, int32_t* sizes);
/**
 * @brief Get the Header from KMessage
 * 
 * @param kmessage Pointer to KMessage
 * @return Pointer to Header
 */
struct Header* get_Header(struct KMessage* kmessage);
/**
 * @brief Set the KMessage's Header
 * 
 * @param kmessage Pointer to KMessage
 * @param header Pointer to Header
 */
void set_Header(struct KMessage* kmessage, struct Header* header);
/**
 * @brief Get the KMessage's frames
 * 
 * @param kmessage Pointer to KMessage
 * @return Frames
 */
unsigned char** get_Frames(struct KMessage* kmessage);
/**
 * @brief Get the KMessage's frame from index
 * 
 * @param kmessage Pointer to KMessage
 * @param i Index
 * @return Frame corresponding to index
 */
unsigned char* get_Frame(struct KMessage* kmessage, int32_t i);
/**
 * @brief Set the KMessage's frames
 * 
 * @param kmessage Pointer to KMessage
 * @param frames Frames (as concatenated 1D array)
 * @param nbFrames Number of frames
 * @param sizes Frames' sizes
 */
void set_Frames(struct KMessage* kmessage, unsigned char* frames, int32_t nbFrames, int32_t* sizes);
/**
 * @brief Get DevID from KMessage
 * 
 * @param kmessage Pointer to KMessage
 * @return DevID string
 */
unsigned char *get_DEVID(struct KMessage* kmessage);
/**
 * @brief Get the size of the KMessage's frame corresponding to the index
 * 
 * @param kmessage Pointer to KMessage
 * @param i Index
 * @return Frame's size
 */
int32_t get_Framesize(struct KMessage* kmessage, int32_t i);
/**
 * @brief Get the DevID's size from KMessage
 * 
 * @param kmessage Pointer to KMessage
 * @return DevID's size
 */
int32_t get_DEVIDSize(struct KMessage* kmessage);
/**
 * @brief Get the KMessage's frames bytes into an array
 * 
 * @param kmessage Pointer to KMessage
 * @return Frames bytes 
 */
unsigned char* get_Frames_Bytes(struct KMessage* kmessage);
/**
 * @brief Get the KMessage's frames bytes size
 * 
 * @param kmessage Pointer to KMessage
 * @return Frames bytes size 
 */
int32_t get_Frames_Bytes_Size(struct KMessage* kmessage);
/**
 * @brief Get the KMessage's full content
 * 
 * @param kmessage Pointer to KMessage
 * @return Bytes 
 */
unsigned char* get_Bytes(struct KMessage* kmessage);
/**
 * @brief Get the KMessage's bytes size
 * 
 * @param kmessage Pointer to KMessage
 * @return Bytes size
 */
int32_t get_Bytes_Size(struct KMessage* kmessage);
/**
 * @brief Get the KMessage's bytes
 * 
 * @param kmessage Pointer to KMessage
 * @return KMessage's bytes  
 */
unsigned char* get_KMessage_Bytes(struct KMessage* kmessage);
/**
 * @brief Get the KMessage's bytes size
 * 
 * @param kmessage Pointer to KMessage
 * @return KMessage's bytes size
 */
int32_t get_KMessage_Bytes_Size(struct KMessage* kmessage);
/**
 * @brief Build a KMessage from data
 * 
 * @param data Input data
 * @return Pointer to KMessage
 */
struct KMessage* build(unsigned char *data);
/**
 * @brief Encore KMessage's type
 * 
 * @param mestype Type
 * @return Encoded type 
 */
unsigned char encode_Type(int32_t mestype);
/**
 * @brief Decode Encoded KMessage's type
 * 
 * @param bhead Encoded type
 * @return Decoded type 
 */
unsigned char decode_Type(unsigned char bhead);
/**
 * @brief Get the KMessage's type
 * 
 * @param kmessage Pointer to KMessage
 * @return Type
 */
unsigned char get_Type(struct KMessage* kmessage);
/**
 * @brief Get the KMessage's subtype
 * 
 * @param kmessage Pointer to KMessage
 * @return SubType
 */
unsigned char get_Subtype(struct KMessage* kmessage);
/**
 * @brief Get the KMessage's address
 * 
 * @param kmessage Pointer to KMessage
 * @return KMessage's address
 */
unsigned char* get_Address(struct KMessage* kmessage);
/**
 * @brief Get the KMessage's address size
 * 
 * @param kmessage Pointer to KMessage
 * @return Address size
 */
int get_Address_size(struct KMessage* kmessage);
/**
 * @brief Get the KMessage's session key
 * 
 * @param kmessage Pointer to KMessage
 * @return Session key
 */
unsigned char* get_SessionKey(struct KMessage* kmessage);
/**
 * @brief Get the KMessage's session key size
 * 
 * @param kmessage Pointer to KMessage
 * @return Session key size
 */
int get_SessionKey_size(struct KMessage* kmessage);
/**
 * @brief Get the KMessage's session IV
 * 
 * @param kmessage Pointer to KMessage
 * @return Session IV
 */
unsigned char* get_SessionIV(struct KMessage* kmessage);
/**
 * @brief Get the KMessage's session IV size
 * 
 * @param kmessage Pointer to KMessage
 * @return Session IV size
 */
int get_SessionIV_size(struct KMessage* kmessage);
/**
 * @brief Set the KMessage's type
 * 
 * @param Kmessage Pointer to KMessage
 * @param type Type
 */
void set_Type(struct KMessage* Kmessage, unsigned char type);
/**
 * @brief Get the minimum version
 * 
 * @param ver Version
 * @return ver & 0001
 */
int32_t get_Min_ver(int32_t ver);
/**
 * @brief Get the maximum version
 * 
 * @param ver Version
 * @return ver >> 1 
 */
int32_t get_Maj_ver(int32_t ver);
/**
 * @brief Get the KMessage's version
 * 
 * @param bhead Type
 * @return bhead & 0x0F
 */
int32_t get_Ver(unsigned char bhead);
/**
 * @brief Get the KMessage's minimum version
 * 
 * @param kmessage Pointer to KMessage
 * @return KMessage's minimum version
 */
int32_t get_Min_ver_KM(struct KMessage* kmessage);
/**
 * @brief Get the KMessage's maximum version
 * 
 * @param kmessage Pointer to KMessage
 * @return KMessage's maximum version
 */
int32_t get_Maj_ver_KM(struct KMessage* kmessage);

/**
 * @brief Create a KMessage with crypted content
 * 
 * @param msg_to_encrypt Message to encrypt
 * @param size Message's size
 * @param key Aes key
 * @param iv Aes IV
 * @return Crypted message 
 */
unsigned char* create_encrypted_message(unsigned char* msg_to_encrypt, int32_t size, uint8_t* key, uint8_t* iv);
/**
 * @brief Print Header
 * 
 * @param header Pointer to Header
 */
void print_Header(struct Header *header);
/**
 * @brief Print KMessage
 * 
 * @param kMessage Pointer to KMessage
 */
void print_KMessage(struct KMessage *kMessage);

/**
 * @brief Check if the KMessage's type is matching the name given
 * 
 * @param kMessage Pointer to KMessage
 * @param type_name Type name string
 * @param encoded Act as a boolean to specify is type should be encoded or not (1 -- Yes ; 0 -- No)
 * @return 1 -- Yes ; 0 -- No
 */
int check_Type(struct KMessage *kMessage, char* type_name, int encoded);

/**
 * @brief Get encoded type
 * 
 * @param type_name Type name
 * @return Encoded type
 */
unsigned char get_encoded_Type(char* type_name);

/**
 * @brief Will return a copy of KMessage
 * 
 * @param kMessage Pointer to KMessage
 * @return Pointer to copy of KMessage
 */
struct KMessage* duplicate_KMessage(struct KMessage *kMessage);

/**
 * @brief Free a KMessage
 * 
 * @param kMessage Pointer to KMessage
 */
void free_KMessage(struct KMessage *kMessage);

/*constexpr
unsigned char secretKey[];*/

#endif
