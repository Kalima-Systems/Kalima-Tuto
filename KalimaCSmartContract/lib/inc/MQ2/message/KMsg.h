#ifndef KMSG_H
#define KMSG_H

/**
 * @file KMsg.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Higher layer of KMessage
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "checksum.h"
#include "DevID.h"
#include "UUID.h"
#include "Header.h"
#include "KMessage.h"
#include "logger.h"
#include "BytesArray.h"
#include "ByteBuffer.h"
#include "prop.h"

/**
 * @brief KMsg structure
 * 
 */
typedef struct KMsg KMsg;
struct KMsg{
    struct KMessage *Kmessage; /**< Pointer to KMessage */
    char *key; /**< Key string */
	int props_size; /**< proplist size */
    List *Kprops; /**< Proplist */
};

/**
 * @brief Create a new empty KMsg with a sequence
 * 
 * @param sequence Sequence
 * @return Pointer to KMsg
 */
KMsg* KMsg_new(int64_t sequence);
/**
 * @brief Builds a KMsg from a KMessage
 * 
 * @param message Pointer to KMessage
 * @return Pointer to KMsg
 */
KMsg* setMessage(struct KMessage *message);
/**
 * @brief Builds a KMsg from parameters
 * 
 * @param devID DevID string
 * @param devID_size DevID size
 * @param type Type
 * @param address Address string
 * @param address_size Address size
 * @param key Key string
 * @param key_size Key size
 * @param seq Sequence
 * @param body Body string
 * @param body_size Body size 
 * @param kProps Proplist
 * @return Pointer to KMsg
 */
KMsg* getMessage(char* devID, int devID_size, char type, char* address, int address_size, char* key, int key_size, int64_t seq, char* body, int body_size, List *kProps);

/**
 * @brief Set Kmsg->Kprops and Kmsg->props_size from frames
 * 
 * @param Kmsg Pointer to KMsg
 */
void decodeProps(KMsg *Kmsg);
/**
 * @brief Duplicated KMsg
 * 
 * @param Kmsg Pointer to KMsg
 * @return Pointer to duplicate of KMsg
 */
KMsg* kmsg_dup(KMsg *Kmsg);
/**
 * @brief Returns a CRC corresponding to the KMsg
 * 
 * @param Kmsg Pointer to KMsg
 * @return CRC
 */
int64_t sign(KMsg *Kmsg);
/**
 * @brief Concatenates the parameters and calculates the sign CRC
 * 
 * @param address Address string
 * @param address_size Address size
 * @param key Key string
 * @param key_size Key size
 * @param body Body string
 * @param body_size Body size
 * @param props Encoded proplist
 * @param props_size Props size
 * @return Sign CRC
 */
int64_t sign_from_inputs(char* address, int address_size, char* key, int key_size, char* body, int body_size, char* props, int props_size);

/**
 * @brief Get the KMsg's key
 * 
 * @param Kmsg Pointer to Kmsg
 * @return Key string
 */
unsigned char *getKey(KMsg *Kmsg);
/**
 * @brief Set the KMsg's string
 * 
 * @param Kmsg Pointer to KMsg
 * @param key Key string
 * @param key_size Key size
 */
void setKey(KMsg *Kmsg, char *key, int key_size);
/**
 * @brief Get the Kmsg's key size
 * 
 * @param Kmsg Pointer to KMsg
 * @return Key size
 */
int getKeySize(KMsg *Kmsg);
/**
 * @brief Set the KMsg's key following a format
 * 
 * @param Kmsg Pointer to KMsg
 * @param format Format string
 * @param format_size Format size
 * @param key Key string
 * @param key_size Key size
 */
void fmtKey(KMsg *Kmsg, char *format, int format_size, char* key, int key_size);

/**
 * @brief Get the KMsg's term
 * 
 * @param Kmsg Pointer to KMsg
 * @return KMsg's term
 */
int64_t getTerm(KMsg *Kmsg);
/**
 * @brief Set the KMsg's term
 * 
 * @param Kmsg Pointer to KMsg
 * @param term Term
 */
void setTerm(KMsg *Kmsg, int64_t term);

/**
 * @brief Get the KMsg's DevID
 * 
 * @param Kmsg Pointer to KMsg
 * @return DevID string
 */
unsigned char* getDevID(KMsg *Kmsg);
/**
 * @brief Set the KMsg's DevID
 * 
 * @param Kmsg Pointer to KMsg
 * @param devId DevID string
 * @param devID_size DevID size
 */
void setDevID(KMsg *Kmsg, char* devId, int devID_size);

/**
 * @brief Get the KMsg's global sequence
 * 
 * @param Kmsg Pointer to KMsg
 * @return Global sequence
 */
int64_t getGlobalSequence(KMsg *Kmsg);
/**
 * @brief Set the KMsg's global sequence
 * 
 * @param Kmsg Pointer to KMsg
 * @param sequence Global sequence
 */
void setGlobalSequence(KMsg *Kmsg, int64_t sequence);
/**
 * @brief Get the KMsg's sequence
 * 
 * @param Kmsg Pointer to KMsg
 * @return Sequence
 */
int64_t getSequence(KMsg *Kmsg);
/**
 * @brief Set the KMsg's sequence
 * 
 * @param Kmsg Pointer to KMsg
 * @param sequence Sequence
 */
void setSequence(KMsg *Kmsg, int64_t sequence);

/**
 * @brief Get the KMsg's body
 * 
 * @param Kmsg Pointer to KMsg
 * @return Body string
 */
unsigned char* getBody(KMsg *Kmsg);
/**
 * @brief Set the KMsg's body
 * 
 * @param Kmsg Pointer to KMsg
 * @param body Body string
 * @param body_size Body size
 */
void setBody(KMsg *Kmsg, char* body, int body_size);
/**
 * @brief Set the KMsg's body following a format
 * 
 * @param Kmsg Pointer to KMsg
 * @param format Format string
 * @param format_size Format size
 * @param body Body string
 * @param body_size Body size
 */
void fmtBody(KMsg *Kmsg, char *format, int format_size, char* body, int body_size);

/**
 * @brief Get the KMsg's UUID
 * 
 * @param Kmsg Pointer to KMsg
 * @return UUID string
 */
unsigned char* getUUID(KMsg *Kmsg);
/**
 * @brief Set the KMsg's UUID
 * 
 * @param Kmsg Pointer to KMsg
 */
void setUUID(KMsg *Kmsg);

/**
 * @brief Get the KMsg's address
 * 
 * @param Kmsg Pointer to KMsg
 * @return Address string
 */
unsigned char* getAddress(KMsg *Kmsg);
/**
 * @brief Get the KMsg's address size
 * 
 * @param Kmsg Pointer to KMsg
 * @return Address size
 */
int getAddressSize(KMsg *Kmsg);
/**
 * @brief Get the KMsg's serialID
 * 
 * @param Kmsg Pointer to KMsg
 * @return SerialID string
 */
unsigned char* getSerialID(KMsg *Kmsg);
/**
 * @brief Set the KMsg's address
 * 
 * @param Kmsg Pointer to KMsg
 * @param address Address string
 * @param address_size Address size
 */
void setAddress(KMsg *Kmsg, char* address, int address_size);

/**
 * @brief Set the KMsg's props from encoded proplist
 * 
 * @param Kmsg Pointer to KMsg
 * @param kProps Encoded proplist
 * @param kProps_size Props size
 */
void setProps(KMsg *Kmsg, char* kProps, int kProps_size);
/**
 * @brief Set the KMsg's props from proplist
 * 
 * @param Kmsg Pointer to KMsg
 * @param kProps Proplist
 */
void setPropsfromlist(KMsg *Kmsg, List *kProps);
/**
 * @brief Get the KMsg's proplist
 * 
 * @param Kmsg Pointer to KMsg
 * @return Proplist 
 */
List* getProps(KMsg *Kmsg);
/**
 * @brief Get the One prop from KMsg matching a name
 * 
 * @param Kmsg Pointer to KMsg
 * @param propName Prop name
 * @return Prop from KMsg's props
 */
unsigned char* getProp(KMsg *Kmsg, char* propName);
/**
 * @brief Set a new prop to KMsg
 * 
 * @param Kmsg Pointer to KMsg
 * @param name Prop name
 * @param name_size Prop name size
 * @param value Prop value
 * @param value_size Prop value size
 */
void setProp(KMsg *Kmsg, char* name, int name_size, char* value, int value_size);

/**
 * @brief Get the KMsg's check
 * 
 * @param Kmsg Pointer to KMsg
 * @return Check string
 */
unsigned char* getCheck(KMsg *Kmsg);
/**
 * @brief Set the KMsg's check
 * 
 * @param Kmsg Pointer to KMsg
 * @param check Check string
 * @param check_size Check size
 */
void setCheck(KMsg *Kmsg, char* check, int check_size);

/**
 * @brief Get the KMsg's sign
 * 
 * @param Kmsg Pointer to KMsg
 * @return Sign
 */
unsigned char* getSign(KMsg *Kmsg);
/**
 * @brief Set the KMsg's sign
 * 
 * @param Kmsg Pointer to KMsg
 * @param sign Sign string
 * @param sign_size Sign size
 */
void setSign(KMsg *Kmsg, char* sign, int sign_size);

/**
 * @brief Get the KMsg's previous sequence
 * 
 * @param Kmsg Pointer to KMsg
 * @return Previous sequence
 */
int64_t getPrevious(KMsg *Kmsg);
/**
 * @brief Set the KMsg's previous sequence
 * 
 * @param Kmsg Pointer to KMsg
 * @param prev Previous sequence
 */
void setPrevious(KMsg *Kmsg, int64_t prev);
/**
 * @brief Get the KMsg's previous term
 * 
 * @param Kmsg Pointer to KMsg
 * @return Previous term
 */
int64_t getPrevTerm(KMsg *Kmsg);
/**
 * @brief Set the KMsg's previous term
 * 
 * @param Kmsg Pointer to KMsg
 * @param term Previous term
 */
void setPrevTerm(KMsg *Kmsg, int64_t term);
/**
 * @brief Get the KMsg's body size
 * 
 * @param Kmsg Pointer to KMsg
 * @return Body size
 */
int getBodySize(KMsg *Kmsg);
/**
 * @brief Get KMessage from KMsg (new malloc)
 * 
 * @param Kmsg Pointer to KMsg
 * @return Pointer to new KMessage
 */
KMessage* getKMessage(KMsg *Kmsg);
/**
 * @brief Print KMsg's informations
 * 
 * @param Kmsg Pointer to KMsg
 */
void dump(KMsg *Kmsg);

/**
 * @brief Free a KMsg
 * 
 * @param Kmsg Pointer to KMsg
 */
void free_KMsg(KMsg *Kmsg);

#endif