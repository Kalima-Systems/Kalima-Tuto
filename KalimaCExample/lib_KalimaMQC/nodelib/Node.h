#ifndef Node_H
#define Node_H

#include <pthread.h>
#include "../netlib/Client.h"
#include "KMsg.h"
#include "config.h"

#define MAX_CLIENT_CONNECTION 10

struct Node{
    uint8_t nbClient;
    struct Client *client[MAX_CLIENT_CONNECTION];
    uint8_t disconnect_index;
    char devid[UUID_SIZE];
    char *serialId;
    int serialId_size;
    Config config;
};
typedef struct Node Node;

Node* create_Node(char* config_input);
void Create_Client(Node *node, char *host, uint16_t port);
void Connect_to_Notaries(Node *node);
void Disconnect_Client(Node *node, char *host, uint16_t port);
void *Disconnect_Handler(void* n);
void send_buffer(Node *node, unsigned char* msg, int size);
void send_to_Notary_Nodes(Node *node, KMessage *Kmessage);
void send_Message_to_Notaries(Node *node, char* msg);
void set_DevID(Node *node);

#endif