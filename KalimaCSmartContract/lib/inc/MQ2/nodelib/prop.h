#ifndef PROP_H
#define PROP_H

/**
 * @file prop.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Props used to send some additional informations concerning the message
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdlib.h>
#include <stdint.h>
#include "LinkedList.h"
#include "BytesArray.h"

/**
 * @brief Prop structure (will be put in a LinkedList)
 * 
 */
typedef struct Prop Prop;
struct Prop
{
    char *key;
    uint16_t key_size;
    char *value;
    uint16_t value_size;
};

/**
 * @brief Creates a new prop
 * 
 * @param key Prop's key
 * @param key_size Prop's key size
 * @param value Prop's value
 * @param value_size Prop's value size
 * @return Pointer to Prop
 */
Prop* new_prop(char *key, uint16_t key_size, char *value, uint16_t value_size);
/**
 * @brief Free a prop
 * 
 * @param prop Pointer to prop
 */
void free_prop(void* prop);
/**
 * @brief Creates a new empty proplist
 * 
 * @return Pointer to List
 */
List* new_propList();
/**
 * @brief Set a Prop to the proplist (will be added at the end of the List)
 * 
 * @param proplist Pointer to List
 * @param key Prop's key
 * @param key_size Prop's key size
 * @param value Prop's value
 * @param value_size Prop's value size
 */
void set_prop(List *proplist, char *key, uint16_t key_size, char *value, uint16_t value_size);
/**
 * @brief Removes a Prop based on its key
 * 
 * @param proplist Pointer to List
 * @param key Key to the Prop to delete
 */
void remove_prop(List *proplist, char* key);
/**
 * @brief Gets the number of Props in a proplist
 * 
 * @param proplist Pointer to List
 * @return Number of Props
 */
uint16_t Number_of_props(List *proplist);
/**
 * @brief Get a Prop in a proplist based on its key
 * 
 * @param proplist Pointer to List
 * @param key Key to the Prop to find
 * @return Prop's value
 */
char* get_prop(List *proplist, char* key);
/**
 * @brief Get the proplist size (matching an encoded List)
 * 
 * @param proplist Pointer to List
 * @return Proplist size
 */
uint16_t get_proplist_size(List *proplist);
/**
 * @brief Print a proplist
 * 
 * @param proplist Pointer to List
 */
void print_proplist(List *proplist);
/**
 * @brief Encode a proplist
 * 
 * @param proplist Pointer to List
 * @return Proplist as a char array
 */
char* encode_props(List *proplist);
/**
 * @brief Decode a prop array
 * 
 * @param propsArray Props array
 * @param propsArray_size Props array size
 * @return Pointer to List
 */
List* decode_props(char* propsArray, int propsArray_size);

#endif