#ifndef CLONE_H
#define CLONE_H

#include <pthread.h>
#include "../KalimaCUtil/skiplist.h"
#include "../KalimaCUtil/BytesArray.h"
#include "../KalimaCUtil/logger.h"
#include "../KalimaCUtil/config.h"
#include "../MQ2/nodelib/Node.h"
#include "memcache.h"

typedef struct Clone Clone;
struct Clone{
    SkipList_t *memcaches;
    SkipList_t *SyncingKCache;
    struct Node *node;
    uint8_t nbNotariesConnected;
    int8_t minimumconnected;
    pthread_t SyncingThread;
};

Clone* Clone_init(struct Node *node);
uint8_t put_msg(Clone* clone, char* address, uint8_t address_size, char* key, uint8_t key_size, char* body, uint16_t body_size, proplist props);
uint8_t put_msg_default(Clone* clone, char* address, uint8_t address_size, char* key, uint8_t key_size, char* body, uint16_t body_size);
uint8_t put_msg_with_ttl(Clone* clone, char* address, uint8_t address_size, char* key, uint8_t key_size, char* body, uint16_t body_size, int ttl);
uint8_t remove_msg(Clone* clone, char* address, uint8_t address_size, char* key, uint8_t key_size);
MemCache* getMemCache(Clone* clone, char* address, uint8_t address_size);
void resyncAddresses(Clone* clone, char* addressList, uint8_t snapshotForAllAddresses);
SkipList_t *getMemCaches(Clone* clone);
void addAddress(Clone* clone, char* address, uint8_t address_size);
//void updateCacheList(Clone* clone);
void set(Clone* clone, char* address, uint8_t address_size, KMessage* message);
void processSnapshotResp(Clone* clone, char* address, uint8_t address_size, KMsg* msg);
void processKalimaAddressList(Clone* clone, KMsg* msg);
void processBeginMemCache(Clone* clone, MemCache* memcache, KMsg* msg);
void processEndMemCache(Clone* clone, MemCache* memcache, KMsg* msg);
void processSnaphotPending(Clone* clone, MemCache* memcache);
void processPubMsg(Clone* clone, KMsg* msg);
uint8_t checkSequence(Clone* clone, KMsg* msg, MemCache* memcache);
void store(Clone* clone, char* address, uint8_t address_size, KMsg* msg, MemCache* memcache);
void print_Clone(Clone* clone);

#endif