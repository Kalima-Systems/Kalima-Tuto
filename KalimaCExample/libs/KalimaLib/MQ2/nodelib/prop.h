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

/**
 * @brief key and value max size
 * 
 */
#define MAX 100

/**
 * @brief element  structure (an element is a prop)
 * 
 */
typedef struct element element;
struct element
{
    char key[MAX];
    uint16_t key_size;
    char value[MAX];
    uint16_t value_size;
    struct element *nxt;
};

/**
 * @brief proplist structure
 * 
 */
typedef element* proplist;

/**
 * @brief Intialize empty proplist
 * 
 * @return proplist 
 */
proplist Initiate_prop_List();
/**
 * @brief Add a new prop to the proplist
 * 
 * @param list Proplist
 * @param key Key string
 * @param key_size Key size
 * @param value Value string
 * @param value_size Value size
 * @return proplist 
 */
proplist set_prop(proplist list, char *key, uint16_t key_size, char *value, uint16_t value_size);
/**
 * @brief Remove a prop from the proplist based on given key
 * 
 * @param list Proplist
 * @param key Key string
 */
void remove_prop(proplist list, char *key);
/**
 * @brief Get number of props in a proplist
 * 
 * @param list Proplist
 * @return Number of props 
 */
uint16_t Number_of_props(proplist list);
/**
 * @brief Get proplist as a string
 * 
 * @param list Proplist
 * @param out Proplist as string
 */
void encode_props(proplist list, char* out);
/**
 * @brief Get proplist from string
 * 
 * @param propsArray Proplist as string
 * @return Proplist
 */
proplist decode_props(uint8_t* propsArray);
/**
 * @brief Get a prop's value from proplist based on given key
 * 
 * @param list Proplist
 * @param key Key string
 * @return Value string
 */
char* get_prop(proplist list, char* key);
/**
 * @brief Clear a proplist
 * 
 * @param list Proplist
 */
void clear_proplist(proplist list);
/**
 * @brief Get the proplist size 
 * 
 * @param list Proplist
 * @return Proplist's size
 */
uint16_t get_proplist_size(proplist list);

#endif