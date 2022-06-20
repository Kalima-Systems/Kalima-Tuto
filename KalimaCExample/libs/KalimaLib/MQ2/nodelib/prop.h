#ifndef PROP_H
#define PROP_H

#include <stdlib.h>
#include <stdint.h>

#define MAX 100

typedef struct element element;
struct element
{
    char key[MAX];
    uint16_t key_size;
    char value[MAX];
    uint16_t value_size;
    struct element *nxt;
};
 
typedef element* proplist;

proplist Initiate_prop_List();
proplist set_prop(proplist list, char *key, uint16_t key_size, char *value, uint16_t value_size);
void remove_prop(proplist list, char *key);
uint16_t Number_of_props(proplist list);
void encode_props(proplist list, char* out);
proplist decode_props(uint8_t* propsArray);
char* get_prop(proplist list, char* key);
void clear_proplist(proplist *list);
uint16_t get_proplist_size(proplist list);

#endif