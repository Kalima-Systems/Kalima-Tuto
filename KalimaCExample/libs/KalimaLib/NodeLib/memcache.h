#ifndef MEMCACHE_H
#define MEMCACHE_H

/**
 * @file memcache.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Handles data received from BlockChain into memcaches
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../KalimaCUtil/LinkedList.h"
#include "../KalimaCUtil/skiplist.h"
#include "../KalimaCUtil/compare.h"
#include "../KalimaCUtil/BytesArray.h"
#include "../MQ2/message/KMsg.h"

/**
 * @brief MemCache Structure
 * 
 */
typedef struct MemCache MemCache;
struct MemCache{
    char* address; /**< MemCache address */
    uint16_t address_size; /**< Address size */
    int64_t sequence; /**< Sequence of last KMessage stored */
    uint8_t server; /**< Flag to specify if node is a server (1 : yes) */
    uint8_t primary;
    SkipList_t *kvmap; /**< KeyValue skiplist with key = KMsg key / value = KMessage */
    SkipList_t *kvqueue; /**< KeyValue skiplist with key = sequence / value = KMsg key */
    List *snapshotPending;
    List *clientPending;
};

/**
 * @brief Initialize memCache if Node is a server
 * 
 * @param primary 
 * @param address Address string
 * @param address_size Address size
 * @return Pointer to MemCache 
 */
MemCache* Memcache_Server_new(uint8_t primary, char* address, int address_size);
/**
 * @brief Initialize memCache if Node is a client
 * 
 * @param address Address string
 * @param address_size Address size
 * @return Pointer to MemCache  
 */
MemCache* Memcache_Client_new(char* address, int address_size);

/**
 * @brief Remove snapshot pending corresponding to KMessage
 * 
 * @param memcache Pointer to MemCache
 * @param message Pointer to KMessage
 * @return Pointer to KMsg removed if done, otherwise NULL 
 */
KMsg* removeSnapshotPending(MemCache* memcache, KMessage *message);

/**
 * @brief Free MemCache
 * 
 * @param memcache Pointer to MemCache
 */
void destroy(MemCache* memcache);

/**
 * @brief Store KMessage to MemCache
 * 
 * @param memcache Pointer to MemCache
 * @param message Pointer to KMessage
 */
void storeLocal(MemCache* memcache, KMessage *message);

/**
 * @brief Get the MemCache last sequence
 * 
 * @param Memcache Pointer to MemCache
 * @return Sequence
 */
int64_t get_MC_Sequence(MemCache* Memcache);
/**
 * @brief Set the MemCache sequence
 * 
 * @param Memcache Pointer to MemCache
 * @param sequence Sequence
 */
void set_MC_Sequence(MemCache* Memcache, int64_t sequence);
/**
 * @brief Increment MemCache sequence
 * 
 * @param memcache Pointer to MemCache
 * @return New sequence
 */
int64_t incr_MC_Sequence(MemCache* memcache);

/**
 * @brief Get the highest remaining sequence stored in MemCache
 * 
 * @param memcache Pointer to MemCache
 * @return Highest remaining sequence
 */
int64_t get_Highest_Remaining_Sequence(MemCache* memcache);
/**
 * @brief Get the lowest remaining sequence stored in MemCache
 * 
 * @param memcache Pointer to MemCache
 * @return Lowest remaining sequence 
 */
int64_t get_Lowest_Remaining_Sequence(MemCache* memcache);

/**
 * @brief Get the key corresponding to a given sequence
 * 
 * @param memcache Pointer to MemCache
 * @param sequNum Sequence
 * @return Key string 
 */
char* get_Sequence_Key(MemCache* memcache, int64_t sequNum);

/**
 * @brief Get the MemCache server flag
 * 
 * @param Memcache Pointer to MemCache
 * @return Server flag
 */
uint8_t get_MC_Server(MemCache* Memcache);
/**
 * @brief Set the MemCache server flag
 * 
 * @param Memcache Pointer to MemCache
 * @param server Server flag
 */
void set_MC_Server(MemCache* Memcache, uint8_t server);
/**
 * @brief Get the MemCache primary flag
 * 
 * @param Memcache Pointer to MemCache
 * @return Primary flag 
 */
uint8_t get_MC_Primary(MemCache* Memcache);
/**
 * @brief Set the MemCache primary flag
 * 
 * @param Memcache Pointer to MemCache
 * @param primary Primary flag
 */
void set_MC_Primary(MemCache* Memcache, uint8_t primary);

/**
 * @brief Get the KMessage Bytes from key
 * 
 * @param memcache Pointer to MemCache
 * @param key Key string
 * @return KMessage bytes 
 */
char* get_KMessage_Bytes_from_key(MemCache* memcache, char* key);
/**
 * @brief Get the MemCache Address
 * 
 * @param memcache Pointer to MemCache
 * @return Address string 
 */
char* get_MC_Address(MemCache* memcache);
/**
 * @brief Get the MemCache Address size
 * 
 * @param memcache Pointer to MemCache
 * @return Address string size
 */
uint16_t get_MC_Address_size(MemCache* memcache);
/**
 * @brief Set the MemCache Address
 * 
 * @param memcache Pointer to MemCache
 * @param address Address string
 * @param address_size Address size
 */
void set_MC_Address(MemCache* memcache, char* address, uint16_t address_size);

/**
 * @brief Get the kvmap
 * 
 * @param memcache Pointer to MemCache
 * @return Pointer to kvmap 
 */
SkipList_t *get_Kvmap(MemCache* memcache);
/**
 * @brief Get the kvqueue
 * 
 * @param memcache Pointer to MemCache
 * @return Pointer to kvqueue 
 */
SkipList_t *get_Kvqueue(MemCache* memcache);
/**
 * @brief Get the MemCache clientPending
 * 
 * @param memcache Pointer to MemCache
 * @return Pointer to clientPending 
 */
List *get_Client_Pending(MemCache* memcache);
/**
 * @brief Get the MemCache snapshotPending
 * 
 * @param memcache Pointer to MemCache
 * @return Pointer to snapshotPending  
 */
List *get_Snapshot_Pending(MemCache* memcache);
/**
 * @brief Set the MemCache kvmap
 * 
 * @param memcache Pointer to MemCache
 * @param kvmap2 Pointer to kvmap to add
 */
void set_Kvmap(MemCache* memcache, SkipList_t *kvmap2);

/**
 * @brief Print kvmap and kvqueue
 * 
 * @param memcache Pointer to MemCache
 */
void print_kvLists(MemCache* memcache);


#endif