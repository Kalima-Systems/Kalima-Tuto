#ifndef Node_H
#define Node_H

/**
 * @file Node.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Main component of a Kalima Node. Will handle all the clients and clone
 * @version 0.1
 * @date 2022-10-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <pthread.h>
#include <stdint.h>
#include "config.h"
#include "opensslUtil.h"
#include "Client.h"
#include "ClientCallback.h"
#include "KMsg.h"
#ifdef CLONELIB
#include "clone.h"
#endif

/**
 * @brief Max number of notaries to connect to
 *
 */
#define MAX_CLIENT_CONNECTION 10

/**
 * @brief Node structure
 *
 */
struct Node
{
    uint8_t nbClient;                             /**< Number of client needed to connect to all the notaries */
    struct Client *client[MAX_CLIENT_CONNECTION]; /**< Array of pointers to Client */
    char *devid;                                  /**< Node's DevID */
    uint8_t devid_size;                           /**< Node's DevID size */
    char *serialId;                               /**< Node's serialID */
    uint16_t serialId_size;                       /**< Node's serialID's size */
    unsigned char *public_key;                    /**< Node's public RSA key */
    int32_t public_key_size;                      /**< Node's public RSA key's size */
    unsigned char *private_key;
    int32_t private_key_size;
    Config *config;                             /**< Pointer to Config */
    void *contract_list;                        /**< Pointer to contract_list */
    ClientCallback *clientcallback;             /**< Pointer to ClientCallback */
    uint8_t joinreqTrigger, subscribeTrigger;   /**< Trigger to join request and subscribe */
    pthread_mutex_t joinreqLock, subscribeLock; /**< Mutex for the triggers */
    uint8_t first_connection;                   /**< Act as a boolean to see if first connection or not (0 -- Yes ; 1 -- No) */
#ifdef CLONELIB
    struct Clone *clone; /**< Pointer to Clone */
#endif
};
typedef struct Node Node;

/**
 * @brief Create a Node
 *
 * @param config_input Config file full path
 * @param contract_list Pointer to contract_list
 * @return Pointer to Node
 */
Node *create_Node(char *config_input, void *contract_list);
/**
 * @brief Handle create_Node() for every Notary
 *
 * @param node Pointer to Node
 * @param clientcallback Pointer to ClientCallback
 */
void Connect_to_Notaries(Node *node, ClientCallback *clientcallback);
/**
 * @brief Send crypted KMessage to notaries
 *
 * @param node Pointer to Node
 * @param Kmessage Pointer to KMessage
 */
void send_KMessage(Node *node, KMessage *Kmessage);
/**
 * @brief Get the Blockchain Snapshot (send a message asking for the snapshot to the BlockChain)
 *
 * @param node Pointer to Node
 * @param address_seq Addresses and sequences of the data you want (separated with ',')
 * @param address_seq_size Size of full message
 * @param snapshotall 1 -- All data; 0 -- data specified before
 */
void get_Snapshot(Node *node, char *address_seq, uint16_t address_seq_size, uint8_t snapshotall);

/**
 * @brief Act as a boolean to determine if every client is connected
 *
 * @param node Pointer to Node
 * @return 1 -- Every client is connected ; 0 -- Some or all clients are disconnected
 */
int Clients_connected(Node *node);

/**
 * @brief Triggers node join request
 *
 * @param node Pointer to Node
 */
void Trigger_joinReq(Node *node);
/**
 * @brief Triggers node subscribe
 *
 * @param node Pointer to Node
 */
void Trigger_subscribe(Node *node);

#endif