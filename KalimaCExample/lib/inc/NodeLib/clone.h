#ifndef CLONE_H
#define CLONE_H

/**
 * @file clone.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Handles data received from BlockChain
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <pthread.h>
#include "skiplist.h"
#include "BytesArray.h"
#include "logger.h"
#include "config.h"
#include "Node.h"
#include "memcache.h"

/**
 * @brief Clone Structure
 * 
 */
typedef struct Clone Clone;
struct Clone{
    SkipList_t *memcaches; /**< List of memcaches */
    SkipList_t *SyncingKCache; /**< List syncing memcaches */
    struct Node *node; /**< Pointer to Node */
    uint8_t nbNotariesConnected; /**< Number of Notary connected */
    int8_t minimumconnected; /**< Minimum of Notary connected required */
    pthread_t SyncingThread; /**< Thread to handle resynchronisation */
};

/**
 * @brief Initialize Clone
 * 
 * @param node Pointer to Node
 * @return Pointer to Clone 
 */
Clone* Clone_init(struct Node *node);

/**
 * @brief Send message to BlockChain
 * 
 * @param clone Pointer to Clone
 * @param address Address string
 * @param address_size Address string size
 * @param key Key string
 * @param key_size Key string size
 * @param body Body string
 * @param body_size Body string size
 * @param props proplist
 * @return 1 -- success, 0 -- failure 
 */
uint8_t put_msg(Clone* clone, char* address, uint8_t address_size, char* key, uint8_t key_size, char* body, uint16_t body_size, List *props);
/**
 * @brief Send message with default proplist to BlockChain
 * 
 * @param clone Pointer to Clone
 * @param address Address string
 * @param address_size Address string size
 * @param key Key string
 * @param key_size Key string size
 * @param body Body string
 * @param body_size Body string size 
 * @return 1 -- success, 0 -- failure  
 */
uint8_t put_msg_default(Clone* clone, char* address, uint8_t address_size, char* key, uint8_t key_size, char* body, uint16_t body_size);
/**
 * @brief Send message with a set ttl to BlockChain
 * 
 * @param clone Pointer to Clone
 * @param address Address string
 * @param address_size Address string size
 * @param key Key string
 * @param key_size Key string size
 * @param body Body string
 * @param body_size Body string size 
 * @param ttl Time to live on Blockchain (and local) memcache
 * @return 1 -- success, 0 -- failure  
 */
uint8_t put_msg_with_ttl(Clone* clone, char* address, uint8_t address_size, char* key, uint8_t key_size, char* body, uint16_t body_size, int ttl);
/**
 * @brief remove message from Blockchain memcache
 * 
 * @param clone Pointer to Clone
 * @param address Address string
 * @param address_size Address string size
 * @param key Key string
 * @param key_size Key string size
 * @return 1 -- success, 0 -- failure 
 */
uint8_t remove_msg(Clone* clone, char* address, uint8_t address_size, char* key, uint8_t key_size);

/**
 * @brief Get memcache with corresponding address
 * 
 * @param clone Pointer to Clone
 * @param address Address string
 * @param address_size Address string size
 * @return Pointer to Memcache
 */
MemCache* getMemCache(Clone* clone, char* address, uint8_t address_size);
/**
 * @brief Resync memcaches from specified addresses
 * 
 * @param clone Pointer to Clone
 * @param addressList List of addresses to resync
 * @param snapshotForAllAddresses Flag (if =1, resync everything)
 */
void resyncAddresses(Clone* clone, char* addressList, uint8_t snapshotForAllAddresses);
/**
 * @brief Get List of memcaches
 * 
 * @param clone Pointer to Clone
 * @return Pointer to SkipList_t 
 */
SkipList_t *getMemCaches(Clone* clone);
/**
 * @brief Add address to memcaches
 * 
 * @param clone Pointer to Clone
 * @param address Address string
 * @param address_size Address string size
 */
void addAddress(Clone* clone, char* address, uint8_t address_size);
//void updateCacheList(Clone* clone);
/**
 * @brief Set KMessage to Clone's memcache corresponding to address
 * 
 * @param clone Pointer to Clone
 * @param address Address of where to add data
 * @param address_size Address size
 * @param message Pointer to KMessage to add
 */
void set(Clone* clone, char* address, uint8_t address_size, KMessage* message);
/**
 * @brief Check if message received hax a good sequence
 * 
 * @param clone Pointer to Clone
 * @param msg Pointer to Kmsg containing message
 * @param memcache Pointer to memcache where message will be added
 * @return 1 -- success, 0 -- failure  
 */
uint8_t checkSequence(Clone* clone, KMsg* msg, MemCache* memcache);
/**
 * @brief Store new data to Clone
 * 
 * @param clone Pointer to Clone
 * @param address Address of where to add data
 * @param address_size Address size
 * @param msg Pointer to Kmsg containing message
 * @param memcache Pointer to Memcache where to add data
 */
void store(Clone* clone, char* address, uint8_t address_size, KMsg* msg, MemCache* memcache);
/**
 * @brief Print Clone
 * 
 * @param clone Pointer to Clone
 */
void print_Clone(Clone* clone);

#endif