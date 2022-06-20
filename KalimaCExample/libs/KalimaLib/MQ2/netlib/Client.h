#ifndef Client_h
#define Client_h

#include <stdint.h>
#include "../../KalimaCUtil/BufferChain.h"
#include "../../KalimaCUtil/skiplist.h"
#include "../../KalimaCUtil/compare.h"
#include "../../KalimaCUtil/aes.h"
#include "../../KalimaCUtil/logger.h"
#include "../../KalimaCUtil/config.h"
#include "../../KalimaCUtil/rsa.h"
#include "../../KalimaCUtil/BytesArray.h"
#include "../message/KMessage.h"
#include "../message/Header.h"
#include "../message/KMsg.h"
#include "../nodelib/Node.h"

#define KEEPALIVE_INTERVAL 3
#define RECONNECT_INTERVAL 5
#define MIN_RECONNECTION_TIME 500000
#define MAX_RECONNECTION_TIME 30000000

struct Client{
    struct Node *node;
    uint8_t sock;
    uint8_t *ip;
    uint8_t ip_size;
    uint16_t port;
    uint8_t awaitingIHY;
    SkipList_t *data_recv;
    Buffer buffer;
    pthread_mutex_t bufferLock;
    pthread_t threadClient;
    unsigned char *aes_key;
    uint8_t aes_key_size;
    unsigned char *aes_iv;
    uint8_t aes_iv_size;
    uint8_t send_join_req;
};
typedef struct Client Client;

Client* Client_init(struct Node *node, uint8_t notary_index);
void *Client_handler(void* cli);
void *Handle_Reconnect(void* cli);
void *send_Client_HB(Client*);
void send_Client_IHY(Client*);
uint8_t connect_Client(Client*);
uint8_t write_Client(Client*, unsigned char *message, uint16_t size);
void send_to_Notary(Client* client, KMessage *Kmessage);
void *read_Client(void*);
void *Client_treat_Read(Client*);
void stop_Client(Client*, uint8_t close);
uint8_t is_connected(Client*);

uint8_t get_awaitingIHY(Client*);
void set_awaitingIHY(Client*, uint8_t value);

int64_t get_Client_Highest_Remaining_Message(Client* client);
int64_t get_Client_Lowest_Remaining_Message(Client* client);

#endif