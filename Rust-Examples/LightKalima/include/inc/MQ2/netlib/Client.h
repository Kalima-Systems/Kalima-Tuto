#ifndef Client_h
#define Client_h

/**
 * @file Client.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Client with socket connection and message handler
 * @version 0.1
 * @date 2022-10-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdint.h>
#include <semaphore.h>
#include "../../KalimaCUtil/BufferChain.h"
#include "../../KalimaCUtil/skiplist.h"
#include "../../KalimaCUtil/compare.h"
#include "../../KalimaCUtil/aesKalima.h"
#include "../../KalimaCUtil/logger.h"
#include "../../KalimaCUtil/config.h"
#include "../../KalimaCUtil/rsaKalima.h"
#include "../../KalimaCUtil/BytesArray.h"
#include "../message/KMessage.h"
#include "../message/Header.h"
#include "../message/KMsg.h"
#include "../nodelib/Node.h"

/**
 * @brief Time set to send basic message to see if connection is still active (here 3sec)
 *
 */
#define KEEPALIVE_INTERVAL 3
/**
 * @brief Reconnection Interval if connection lost (here 5sec)
 *
 */
#define RECONNECT_INTERVAL 5
/**
 * @brief Minimum reconnection Interval if connection lost (reconnection interval will increase with each failure)
 *
 */
#define MIN_RECONNECTION_TIME 500000
/**
 * @brief Maximum reconnection Interval if connection lost (reconnection interval will increase with each failure)
 *
 */
#define MAX_RECONNECTION_TIME 30000000

/**
 * @brief Client Structure
 *
 */
struct Client
{
    struct Node *node;                                                                    /**< Pointer to Node */
    int *sock;                                                                            /**< Client socket */
    uint8_t *ip;                                                                          /**< IP address of server to connect to */
    uint8_t ip_size;                                                                      /**< IP address size */
    uint16_t port;                                                                        /**< Port of server to connect to */
    uint8_t awaitingIHY;                                                                  /**< Act as boolean to see if a message has been received since last KEEPALIVE_INTERVAL */
    uint8_t messageSent;                                                                  /**< Act as boolean to see if a message has been sent since last KEEPALIVE_INTERVAL */
    pthread_mutex_t msgsentLock;                                                          /**< Mutex protecting messageSent */
    SkipList_t *data_recv, *pending_data, *write_data, *pending_message;                  /**< Different skiplist that act as pending buffers (data_recv : data received / pending_data : data to be sent / write_data : to be sure that data is received by blockchain / pending_message : stock pendings when deconnected) */
    Buffer *buffer;                                                                       /**< Buffer to be treated (Concatenation of data_recv) */
    pthread_mutex_t recvLock, pendingdLock, writeLock, sockLock, connectLock, rejoinLock; /**< Mutex protecting key informations */
#if __linux__
    sem_t rec_sem, send_sem; /**< Semaphores */
#elif __APPLE__
    sem_t *rec_sem, *send_sem;
#endif
    pthread_t threadClient;  /**< Client thread initiated by Node */
    unsigned char *aes_key;  /**< Aes key string */
    uint8_t aes_key_size;    /**< Aes key size */
    unsigned char *aes_iv;   /**< Aes IV string */
    uint8_t aes_iv_size;     /**< Aes IV size */
    uint8_t aes_received;    /**< Act as boolean to see if the aes informations have been received from joinResp (0 -- No ; 1 -- Yes) */
    uint8_t rejoin_received; /**< Act as boolean to see if the aes informations have been received from joinResp (0 -- No ; 1 -- Yes) */
};
typedef struct Client Client;

/**
 * @brief Initialize Client
 *
 * @param node Pointer to Node
 * @param notary_index Notary's index (from Node, corresponding to config file)
 * @return Pointer to Client
 */
Client *Client_init(struct Node *node, uint8_t notary_index);
/**
 * @brief Client Main Thread (will handle connection and the 4 other threads)
 *
 * @param cli Pointer to Client
 * @return void*
 */
void *Client_handler(void *cli);

/**
 * @brief Will write new data in send_pending skiplist
 *
 * @param client Pointer to Client
 * @param message Message to add
 * @param size Message size
 * @return On success : 1 @n 
 *         On failure : -1
 */
int8_t write_Client(Client *client, unsigned char *message, uint16_t size);
/**
 * @brief Encrypt and call write_Client()
 *
 * @param client Pointer to Client
 * @param Kmessage Pointer to KMessage to send
 * @return On success : 1 @n 
 *         On failure : -1
 */
int8_t send_to_Notary(Client *client, KMessage *Kmessage);

/**
 * @brief Act as a boolean to see if Client is connected to a Notary
 *
 * @param client Pointer to Client
 * @return 1 -- Connected ; 0 -- Not connected
 */
uint8_t is_connected(Client *client);

/**
 * @brief
 *
 * @param client
 */
void client_pendingm_to_pendingd(Client *client);

#endif