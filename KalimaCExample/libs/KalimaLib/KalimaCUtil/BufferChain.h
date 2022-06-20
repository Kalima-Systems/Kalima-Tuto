#ifndef BUFFERCHAIN_H
#define BUFFERCHAIN_H

#include <stdlib.h>
#include <stdint.h>

#define SEND_SIZE 8000
#define BUFFER_SIZE 16000
#define MAX_BUFFER_SIZE 64000

struct Buffer{
    uint8_t data[MAX_BUFFER_SIZE];
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
Buffer Buffer_add(Buffer buf, uint8_t* data, uint16_t data_size);
Buffer Buffer_delete_data(Buffer buf, uint16_t data_size);
bufferlist Initiate_Buffer_List();
bufferlist add_Buffer(bufferlist, uint8_t*, uint16_t);
bufferlist del_first_Buffer(bufferlist);
void delete_BufferChain(bufferlist list);
void add_to_buffer(buf_element*, uint8_t*, uint16_t);
bufferlist add_to_bufferlist(bufferlist, uint8_t*, uint16_t);
uint16_t Buffer_Nb(bufferlist);
void set_message_size(buf_element*);

#endif