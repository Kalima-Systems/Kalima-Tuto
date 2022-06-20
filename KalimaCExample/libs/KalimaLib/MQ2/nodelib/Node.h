#ifndef Node_H
#define Node_H

#include <pthread.h>
#include <stdint.h>
#include "../../KalimaCUtil/config.h"
#include "../netlib/Client.h"
#include "../netlib/ClientCallback.h"
#include "../message/KMsg.h"
#ifdef CLONELIB
    #include "../../NodeLib/clone.h"
#endif

#define MAX_CLIENT_CONNECTION 10

struct Node{
    uint8_t nbClient;
    struct Client *client[MAX_CLIENT_CONNECTION];
    uint8_t disconnect_index;
    char *devid;
    uint8_t devid_size;
    char *serialId;
    uint16_t serialId_size;
    unsigned char *public_key;
    int32_t public_key_size;
    Config *config;
    List *script_list;
    ClientCallback* clientcallback;
    #ifdef CLONELIB
        struct Clone* clone;
    #endif
};
typedef struct Node Node;

Node* create_Node(char* config_input, List *script_list);
void Create_Client(Node *node, uint8_t notary_index);
void Connect_to_Notaries(Node *node, ClientCallback* clientcallback);
void Disconnect_Client(Node *node, uint8_t* ip, uint16_t port);
void *Disconnect_Handler(void* n);
void send_buffer(Node *node, unsigned char* msg, uint16_t size);
void send_KMessage(Node *node, KMessage *Kmessage);
void send_Message_to_Notaries(Node *node, char* msg);
void send_stresstest(Node *node, uint16_t number);
void set_DevID(Node *node);
void set_public_key(Node *node);

void *Handle_Special_Messages(void* n);

void join_Req(struct Client *client);
void join_Req_all(Node* node);
void subscribe(struct Client *client);
void subscribe_all(Node *node);
void get_Snapshot(Node *node, char* address_seq, uint16_t address_seq_size, uint8_t snapshotall);

#endif