#ifndef CLIENTCALLBACK_H
#define CLIENTCALLBACK_H

/**
 * @file ClientCallback.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Callback set in Client Treat Read to allow user to do what he wants with data received in higher layers
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../message/KMessage.h"
#include "Client.h"

/**
 * @brief Not set
 * 
 */
typedef void (*ClientCallback_send)  (KMessage* Kmessage);
/**
 * @brief Not set
 * 
 */
typedef void (*ClientCallback_onNewAddress)  (void* node, char* address, uint8_t address_size);
/**
 * @brief Not set
 * 
 */
typedef void (*ClientCallback_onAddressSynchronized)  (void* node, char* address, uint8_t address_size);
/**
 * @brief Notary node rejected join request
 * 
 */
typedef void (*ClientCallback_onReject)  (void* client);

/**
 * @brief Structure containing functions
 * 
 */
struct ClientCallback{
    ClientCallback_send send;
    ClientCallback_onNewAddress onNewAddress;
    ClientCallback_onAddressSynchronized onAddressSynchronized;
    ClientCallback_onReject onReject;
};
typedef struct ClientCallback ClientCallback;

/**
 * @brief Create ClientCallback to send to Node with user's created functions
 * 
 * @param send Send function
 * @param onNewAddress onNewAddress function
 * @param onAddressSynchronized onAddressSynchronized function
 * @param onReject onReject function
 * @return Pointer to ClientCallback 
 */
ClientCallback* new_ClientCallback(ClientCallback_send send, ClientCallback_onNewAddress onNewAddress, ClientCallback_onAddressSynchronized onAddressSynchronized, ClientCallback_onReject onReject);

#endif