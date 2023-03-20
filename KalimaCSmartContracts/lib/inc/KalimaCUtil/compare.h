#ifndef COMPARE_H
#define COMPARE_H

/**
 * @file compare.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Compare functions for skiplist.h
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>
#include "skiplist.h"
#include "BytesArray.h"

/**
 * @brief Objet for skiplist with key/value
 * 
 */
typedef struct KeyValueObj{
    void *key; /**< Key pointer */
    int key_size; /**< Key size */
    void *value; /**< Value pointer */
	int value_size; /**< Value size */
} KeyValueObj;
/**
 * @brief Objet for skiplist with only key
 * 
 */
typedef struct KeyObj{
    void *key; /**< Key pointer */
    int key_size; /**< Key size */
} KeyObj;

/**
 * @brief Initialize a KeyValueObj
 * 
 * @param key Key pointer
 * @param key_size Key size
 * @param value Value pointer
 * @param value_size Value size
 * @return Pointer to KeyValueObj 
 */
KeyValueObj *createKeyValueObj(void *key, int key_size, void *value, int value_size);
/**
 * @brief Initialize a KeyObj
 * 
 * @param key Key pointer
 * @param key_size Key size
 * @return Pointer to KeyObj 
 */
KeyObj *createKeyObj(void *key, int key_size);

/**
 * @brief Free a node's key (which is a KeayValueObj)
 * 
 * @param obj Pointer skiplistnode's key
 */
void free_KeyValueObj(void* key);
/**
 * @brief Free a node's key (which is a KeayValueObj)
 * 
 * @param KO Pointer skiplistnode's key
 */
void free_KeyObj(void* key);

/**
 * @brief Compare keys if SkipListNode_t key is a string
 * 
 * @param obj1 SkipListNode_t 1
 * @param obj2 SkipListNode_t 2
 * @return Same format as strcmp
 */
int CmpKey(SkipListNode_t *obj1, SkipListNode_t *obj2);
/**
 * @brief Compare keys if SkipListNode_t key is a KeyObj
 * 
 * @param obj1 SkipListNode_t 1
 * @param obj2 SkipListNode_t 2
 * @return Same format as strcmp
 */
int CmpKeyObj(SkipListNode_t *obj1, SkipListNode_t *obj2);
/**
 * @brief Compare keys if SkipListNode_t key is a KeyValueObj
 * 
 * @param obj1 SkipListNode_t 1
 * @param obj2 SkipListNode_t 2
 * @return Same format as strcmp
 */
int CmpKeyValueObj(SkipListNode_t *obj1, SkipListNode_t *obj2);

/**
 * @brief Compare keys if SkipListNode_t key is an integer
 * 
 * @param obj1 SkipListNode_t 1
 * @param obj2 SkipListNode_t 2
 * @return Same format as strcmp
 */
int CmpInt(SkipListNode_t *obj1, SkipListNode_t *obj2);
/**
 * @brief Compare keys if SkipListNode_t key is an integer in KeyValueObj
 * 
 * @param obj1 SkipListNode_t 1
 * @param obj2 SkipListNode_t 2
 * @return Same format as strcmp
 */
int CmpIntKV(SkipListNode_t *obj1, SkipListNode_t *obj2);

/**
 * @brief Compare adding order in skiplist
 * 
 * @param obj1 SkipListNode_t 1
 * @param obj2 SkipListNode_t 2
 * @return Same format as strcmp
 */
int CmpOrder(SkipListNode_t *obj1, SkipListNode_t *obj2);

void myFree();

#endif