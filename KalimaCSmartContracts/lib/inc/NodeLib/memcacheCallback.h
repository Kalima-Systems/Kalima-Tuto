#ifndef MEMCACHECALLBACK_H
#define MEMCACHECALLBACK_H

/**
 * @file MemCacheCallback .h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Callback set in memcache to allow user to do what he wants with data received in higher layers
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * @brief Function Interface set in memcache. User needs to create his own putData function with same format and if will get the data added to memcache
 * 
 */
typedef void (*MemCacheCallback_putData)  (void* clone, KMessage* Kmessage);
/**
 * @brief Function Interface set in memcache. User needs to create his own removeData function with same format and if will get the data removed from the memcache
 * 
 */
typedef void (*MemCacheCallback_removeData)  (void* clone, KMessage* Kmessage);

/**
 * @brief Structure containing functions
 * 
 */
struct MemCacheCallback{
    MemCacheCallback_putData putData;
    MemCacheCallback_removeData removeData;
    char* getAddress;
};
typedef struct MemCacheCallback MemCacheCallback;

/**
 * @brief Create MemCacheCallback to send to Clone with user's created functions
 * 
 * @param putData putData function
 * @param removeData removeData function
 * @param getAddress getAddress char*
 * @return Pointer to MemCacheCallback 
 */
MemCacheCallback* new_MemCacheCallback(MemCacheCallback_putData putData, MemCacheCallback_removeData removeData, char* getAddress);
#endif