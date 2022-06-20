#ifndef CLIENTCALLBACK_H
#define CLIENTCALLBACK_H

#include "../message/KMessage.h"
#include "Client.h"

typedef void (*ClientCallback_send)  (KMessage* Kmessage);
typedef void (*ClientCallback_putData)  (void* client, KMessage* Kmessage);
typedef void (*ClientCallback_onNewAddress)  (char* address, uint8_t address_size);
typedef void (*ClientCallback_onAddressSynchronized)  (char* address, uint8_t address_size);

struct ClientCallback{
    ClientCallback_send send;
    ClientCallback_putData putData;
    ClientCallback_onNewAddress onNewAddress;
    ClientCallback_onAddressSynchronized onAddressSynchronized;
};
typedef struct ClientCallback ClientCallback;

ClientCallback* new_ClientCallback(ClientCallback_send send, ClientCallback_putData putData, ClientCallback_onNewAddress onNewAddress, ClientCallback_onAddressSynchronized onAddressSynchronized);

#endif