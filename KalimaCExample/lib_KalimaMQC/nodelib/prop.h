#ifndef PROP_H
#define PROP_H

#include <stdlib.h>
#include <stdint.h>

#define MAX 100

typedef struct element element;
struct element
{
    char key[MAX];
    int key_size;
    char value[MAX];
    int value_size;
    struct element *nxt;
};
 
typedef element* proplist;

proplist Initiate_prop_List();
proplist set_prop(proplist list, char *key, int key_size, char *value, int value_size);
void remove_prop(proplist list, char *key);
int Number_of_props(proplist list);
void encode_props(proplist list, char* out);
proplist decode_props(proplist list, uint8_t* propsArray);
char* get_prop(proplist list, char* key);
void clear_proplist(proplist *list);
int get_proplist_size(proplist list);

#endif