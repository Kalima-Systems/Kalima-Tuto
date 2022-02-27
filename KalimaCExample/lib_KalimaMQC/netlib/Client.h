#ifndef Client_h
#define Client_h

#include <stdint.h>
#include "../message/KMessage.h"
#include "../message/Header.h"
#include "Buffer/BufferChain.h"
#include "../crypto/aes.h"
#include "../nodelib/logger.h"
#include "../nodelib/config.h"
#include "../nodelib/KMsg.h"

#define KEEPALIVE_INTERVAL 3
#define RECONNECT_INTERVAL 5
#define BUFFER_SIZE 1000
#define MIN_RECONNECTION_TIME 500000
#define MAX_RECONNECTION_TIME 30000000

struct Client{
    uint8_t sock;
    uint8_t *ip;
    uint16_t port;
    uint8_t awaitingIHY;
    Buffer buffer;
    bufferlist BufferChain;
    pthread_t threadClient;
    pthread_mutex_t bufferLock;
    pthread_cond_t cond, cond2;
    Config config;
    char devid[UUID_SIZE];
};
typedef struct Client Client;

Client* Client_init(uint8_t *ip, uint16_t port, Config config, char* devid);
void *Client_handler(void* cli);
void *send_Client_HB(Client*);
void send_Client_IHY(Client*);
uint8_t connect_Client(Client*);
int write_Client(Client*, unsigned char *message, uint16_t size);
void *read_Client(void*);
void *Client_treat_Read(Client*);
void stop_Client(Client*, uint8_t close);
uint8_t is_connected(Client*);

uint8_t get_awaitingIHY(Client*);
void set_awaitingIHY(Client*, uint8_t value);

void subscribe(Client *client);

#endif