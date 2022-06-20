#ifndef MEMCACHE_H
#define MEMCACHE_H

#include "../KalimaCUtil/LinkedList.h"
#include "../KalimaCUtil/skiplist.h"
#include "../KalimaCUtil/compare.h"
#include "../KalimaCUtil/BytesArray.h"
#include "../MQ2/message/KMsg.h"


typedef struct MemCache MemCache;
struct MemCache{
    char* address;
    uint16_t address_size;
    int64_t sequence;
    uint8_t server;
    uint8_t primary;
    SkipList_t *kvmap;
    SkipList_t *kvqueue;
    List *snapshotPending;
    List *clientPending;
};

MemCache* Memcache_Server_new(uint8_t primary, char* address, int address_size);
MemCache* Memcache_Client_new(char* address, int address_size);

KMsg* removeSnapshotPending(MemCache* memcache, KMessage *message);

void destroy(MemCache* memcache);

void storeLocal(MemCache* memcache, KMessage *message);

int64_t get_MC_Sequence(MemCache* Memcache);
void set_MC_Sequence(MemCache* Memcache, int64_t sequence);
int64_t incr_MC_Sequence(MemCache* memcache);

int64_t get_Highest_Remaining_Sequence(MemCache* memcache);
int64_t get_Lowest_Remaining_Sequence(MemCache* memcache);

char* get_Sequence_Key(MemCache* memcache, int64_t sequNum);

uint8_t get_MC_Server(MemCache* Memcache);
void set_MC_Server(MemCache* Memcache, uint8_t server);
uint8_t get_MC_Primary(MemCache* Memcache);
void set_MC_Primary(MemCache* Memcache, uint8_t primary);

char* get_KMessage_Bytes_from_key(MemCache* memcache, char* key);
char* get_MC_Address(MemCache* memcache);
uint16_t get_MC_Address_size(MemCache* memcache);
void set_MC_Address(MemCache* memcache, char* address, uint16_t address_size);

SkipList_t *get_Kvmap(MemCache* memcache);
SkipList_t *get_Kvqueue(MemCache* memcache);
List *get_Client_Pending(MemCache* memcache);
List *get_Snapshot_Pending(MemCache* memcache);
void set_Kvmap(MemCache* memcache, SkipList_t *kvmap2);

void print_kvLists(MemCache* memcache);


#endif