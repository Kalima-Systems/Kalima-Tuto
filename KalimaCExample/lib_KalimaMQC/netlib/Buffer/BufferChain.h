#ifndef BUFFERCHAIN_H
#define BUFFERCHAIN_H

#include <stdlib.h>
#include <stdint.h>

#define BUFFER_SIZE 1000
#define TRANSITION_SIZE 1000

struct Buffer{
    uint8_t data[TRANSITION_SIZE];
    uint16_t BufferSize;
};
typedef struct Buffer Buffer;
 
typedef struct buf_element buf_element;
struct buf_element
{
    uint8_t buffer[BUFFER_SIZE];
    uint16_t BufferSize;
    uint16_t KMessageSize;
    struct buf_element *nxt;
};
 
typedef buf_element* bufferlist;

struct Buffer create_Buffer();
bufferlist Initiate_Buffer_List();
bufferlist add_Buffer(bufferlist, uint8_t*, int);
bufferlist del_first_Buffer(bufferlist);
void delete_BufferChain(bufferlist list);
void add_to_buffer(buf_element*, uint8_t*, int);
bufferlist add_to_bufferlist(bufferlist, uint8_t*, int);
int Buffer_Nb(bufferlist);
void set_message_size(buf_element*);

#endif