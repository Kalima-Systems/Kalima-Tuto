#ifndef CHAINEDLIST_H
#define CHAINEDLIST_H

/**
 * @file LinkedList.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief LinkedList structure and usefull functions
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
/**
 * @brief Free function used in free and delete functions (with a List element as parameter)
 * 
 */
typedef void (*LinkedList_freeFunction)  (void* elem);
/**
 * @brief Compare function used in get_index (with data you want to find as first and element->data as second)
 * 
 */
typedef int (*LinkedList_cmpFunction)  (void *ptr1, void*ptr2);

/**
 * @brief Element of a LinkedList
 * 
 */
typedef struct Element Element;
struct Element
{
    void* data; /**< Data of an Element */
    Element *next; /**< Pointer to next Element */
};

/**
 * @brief LinkedList structure
 * 
 */
typedef struct List List;
struct List
{
    Element *head; /**< Pointer to first Element */
    LinkedList_cmpFunction cmpFunction; /**< Compare function */
    LinkedList_freeFunction freeFunction; /**< Free function */
};

/**
 * @brief Initialize empty List
 * 
 * @return Pointer to List 
 */
List* new_LinkedList(LinkedList_cmpFunction cmpFunction, LinkedList_freeFunction freeFunction);
/**
 * @brief Set list compare function
 * 
 * @param list Pointer to List
 * @param CmpFunction Compare function
 */
void list_set_compare(List *list, LinkedList_cmpFunction cmpFunction);
/**
 * @brief Set list free function
 * 
 * @param list Pointer to List
 * @param freeFunction Free function
 */
void list_set_free(List *list, LinkedList_freeFunction freeFunction);
/**
 * @brief Set list functions
 * 
 * @param list Pointer to List
 * @param CmpFunction Compare function
 * @param freeFunction Free function
 */
void list_set_functions(List *list, LinkedList_cmpFunction cmpFunction, LinkedList_freeFunction freeFunction);
/**
 * @brief Free a List
 * 
 * @param list Pointer to List
 */
void free_List(List *list);
/**
 * @brief Get Element at index
 * 
 * @param list Pointer to List
 * @param index index
 * @return pointer to Element
 */
Element* list_get_element(List *list, int index);
/**
 * @brief Checks if a List contains an Element
 * 
 * @param list Pointer to List
 * @param x Pointer to Element
 * @return index (-1 if not found)
 */
int list_contains(List *list, Element* x);
/**
 * @brief Insert data at start of List
 * 
 * @param list Pointer to List
 * @param new_data Data to add
 */
void insert_at_start_of_list(List *list, void* new_data);
/**
 * @brief Insert data at end of List
 * 
 * @param list Pointer to List
 * @param new_data Data to add
 */
void insert_at_end_of_list(List *list, void* new_data);
/**
 * @brief Insert data at given position
 * 
 * @param list Pointer to List
 * @param new_data Data to add
 * @param position Position where to add data
 */
void insert_at_position(List *list, void* new_data, int position);
/**
 * @brief Delete first Element from List
 * 
 * @param list Pointer to List
 */
void delete_first_element(List *list);
/**
 * @brief Delete last Element from List
 * 
 * @param list Pointer to List
 */
void delete_last_element(List *list);
/**
 * @brief Delete Element at position from List
 * 
 * @param list Pointer to List
 * @param position Position
 */
void delete_at_position(List *list, int position);
/**
 * @brief Get index of data from List
 * @details Will compare the data specified as parameter and the List's Element->data
 * 
 * @param list Pointer to List
 * @param elem Data to find
 * @return Index
 */
int list_get_index(List *list, void* elem);
/**
 * @brief Get number of Element in List
 * 
 * @param list Pointer to List
 * @return Number of Element in List
 */
int nb_of_elements(List *list);
/**
 * @brief Print List
 * @details Must use a matching print function to print the data (ex : "test", print_string)
 * 
 * @param list Pointer to List
 * @param prt Print function
 */
void print_list(List*list, void (*prt)(void *));
/**
 * @brief Print integer from List
 * 
 * @param x Integer as void*
 */
void print_int(void *x);
/**
 * @brief Print float from List
 * 
 * @param x float as void*
 */
void print_float(void *x);
/**
 * @brief Print string from List
 * 
 * @param x string as void*
 */
void print_string(void *str);
/**
 * @brief Compare function for integers
 * 
 * @param x Integer 1 as void*
 * @param y Integer 2 as void*
 * @return Similar to strcmp 
 */
int list_int_cmp(void *x, void* y);
/**
 * @brief Compare function for strings
 * 
 * @param x String 1 as void*
 * @param y String 2 as void*
 * @return Similar to strcmp 
 */
int list_string_cmp(void *x, void* y);

#endif