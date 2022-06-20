#ifndef CHAINEDLIST_H
#define CHAINEDLIST_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef struct Element Element;
struct Element
{
    void* data;
    Element *next;
};

typedef struct List List;
struct List
{
    Element *head;
    
};
List* new_LinkedList();
void free_List(List *list);
Element* list_get_element(List *list, int index);
int list_contains(List *list, Element* x);
void insert_at_start_of_list(List *list, void* new_data);
void insert_at_end_of_list(List *list, void* new_data);
void insert_at_position(List *list, void* new_data, int position);
void delete_first_element(List *list);
void delete_last_element(List *list);
void delete_at_position(List *list, int position);
void delete(List*list, void* data);
void print_list(List*list, void (*prt)(void *));
int nb_of_elements(List *list);
void print_int(void *x);
void print_float(void *x);
void print_string(void *str);

#endif