#include "BufferChain.h"
#include <stdio.h> /*printf*/
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG

Buffer create_Buffer(){ 
    Buffer buffer;
    buffer.BufferSize = 0;
    return buffer;
}

bufferlist Initiate_Buffer_List(){
    bufferlist bList = NULL;
    return bList;
}

bufferlist add_Buffer(bufferlist list, uint8_t* buffer, int bSize){
    buf_element* newElement = malloc(sizeof(buf_element));
    newElement->nxt = NULL;

    memcpy(newElement->buffer, buffer, bSize);
    newElement->BufferSize = bSize;
    set_message_size(newElement);
 
    if(list == NULL){
        return newElement;
    }
    else{
        buf_element* temp=list;
        while(temp->nxt != NULL){
            temp = temp->nxt;
        }
        temp->nxt = newElement;
        return list;
    }
}

bufferlist del_first_Buffer(bufferlist list){
    if(list != NULL){
        buf_element* sendBack = list->nxt;
        free(list);
        return sendBack;
    }
    else{
        return NULL;
    }
}

void delete_BufferChain(bufferlist list){
    buf_element* current = list;
    buf_element* next = NULL;
    while(current != NULL){
        next = current->nxt;
        free(current);
        current = next;
    }
    list = NULL;
}

void add_to_buffer(buf_element* elem, uint8_t* data, int size){
    int i;
    for(i=0;i<size;i++){ /*add data to buffer*/
        elem->buffer[elem->BufferSize+i] = data[i];
    }
    elem->BufferSize = elem->BufferSize + size;/*edit buffersize*/
    set_message_size(elem); /*Edit KMessageSize*/
    #ifdef DEBUG
        printf("size test : %d\n", size);
        printf("bSize test : %d\n", elem->BufferSize);
        printf("kmSize test : %d\n", elem->KMessageSize);
    #endif
}

bufferlist add_to_bufferlist(bufferlist list, uint8_t* buffer, int bSize){
    #ifdef DEBUG
        printf("Entry size : %d\n", bSize);
    #endif
    int BuffSizeTemp, excess;
    if(Buffer_Nb(list) == 0){ /*If no buffer*/
        if(bSize<4){ /*If we have less than what's necessary for KMessageSize*/
            list = add_Buffer(list, buffer, bSize); /*New buffer with entry buffer*/
            return list;
        }
        else{ /*If we have enough to get KMessageSize*/
            int KMessageSize = (int) buffer[3] + ((int) buffer[2] << 8) + ((int) buffer[1] << 16) + ((int) buffer[0] << 24);
            if(bSize<=KMessageSize){ /*If we have an entry to complete or less, we create with the whole entry buffer*/
                list = add_Buffer(list, buffer, bSize);
                return list;
            }
            if(bSize>KMessageSize){ /*If we have an excess*/
                #ifdef DEBUG
                    printf("bSize : %d\n", bSize);
                    printf("kSize : %d\n", KMessageSize); 
                #endif
                list = add_Buffer(list, buffer, KMessageSize); /*We add enough to calculate KMessageSize*/
                bSize = bSize - KMessageSize; /*We delete the 4 sent to the buffer*/
                memcpy(buffer, buffer+KMessageSize, bSize); /*Copy buffer exept 4 first*/
            }
        }
    }
    buf_element* tmp = list; /*Pointer on last elem*/
    if(Buffer_Nb(list)>0){
        while(tmp->nxt != NULL){
            tmp = tmp->nxt;
        }
    }
    while(bSize>0){ /*While we have data in entry buffer*/
        if(tmp->BufferSize == tmp->KMessageSize){ /*If the last is full but not treated*/
            if(bSize <= 4){ /* If we have less than 4 octets (the number to determine kMessageSize) we have and finish function*/
                list = add_Buffer(list, buffer, bSize); /*We create a new one*/
                return list; 
            }
            list = add_Buffer(list, buffer, 4); /*If we have 4 or more, we add a new buffer with just enough to get KMessageSize*/
            tmp = tmp->nxt;
            bSize = bSize - 4; /*We delete the 4 sent to the buffer*/
            memcpy(buffer, buffer+4, bSize); /*Copy buffer exept 4 first*/
        }
        if(tmp->BufferSize < 4 && tmp->BufferSize+bSize >= 4){ /*If we can't get KMessageSize and enough data to add to get it*/
            BuffSizeTemp = tmp->BufferSize;
            add_to_buffer(tmp, buffer, 4-tmp->BufferSize); /*We add */
            bSize = bSize - 4 + BuffSizeTemp; /*Delete what we added*/
            memcpy(buffer, buffer+4-BuffSizeTemp, bSize);
        }
        if(tmp->BufferSize < 4 && tmp->BufferSize+bSize < 4){ /*If we can't get KMessageSize and not enough data to add to get it*/
            add_to_buffer(tmp, buffer, bSize); /*We add */
            return list;
        }
        if(tmp->BufferSize+bSize <= tmp->KMessageSize){ /*If we fill without excess*/
            add_to_buffer(tmp, buffer, bSize); /*We add and end*/
            return list;
        }
        if(tmp->BufferSize+bSize > tmp->KMessageSize){ /*If we fill with excess*/
            set_message_size(tmp);
            BuffSizeTemp = tmp->BufferSize;
            excess = tmp->BufferSize + bSize - tmp->KMessageSize; /*We get number of excess*/
            #ifdef DEBUG
                printf("bufferSize : %d\n", tmp->BufferSize);
                printf("bSize : %d\n", bSize);
                printf("kmSize : %d\n", tmp->KMessageSize);
                printf("excess : %d\n", excess);
            #endif
            add_to_buffer(tmp, buffer, bSize-excess); /*We add minus the excess*/
            bSize = bSize - tmp->KMessageSize + BuffSizeTemp; /*Delete what we added*/
            if(bSize >0){
                memcpy(buffer, buffer+tmp->KMessageSize-BuffSizeTemp, bSize); /*delete data treated*/
            }
            else{
                return list;
            }
            #ifdef DEBUG
                usleep(10000);
            #endif
        }
    }
    return list;
}

int Buffer_Nb(bufferlist list){
    if(list == NULL)
        return 0;
    return Buffer_Nb(list->nxt)+1;
}

void set_message_size(buf_element* elem){
    if(elem->BufferSize >= 4){
        elem->KMessageSize = (int) elem->buffer[3] + ((int) elem->buffer[2] << 8) + ((int) elem->buffer[1] << 16) + ((int) elem->buffer[0] << 24);
    }
    else{
        elem->KMessageSize = 0;
    }
}

