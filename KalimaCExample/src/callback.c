#include "callback.h"

ClientCallback* new_ClientCallback(ClientCallback_send send, ClientCallback_putData putData, ClientCallback_onNewAddress onNewAddress, ClientCallback_onAddressSynchronized onAddressSynchronized, ClientCallback_onReject onReject){
    ClientCallback* cb = malloc(sizeof(ClientCallback));
    if(cb == NULL){
      return NULL;
    }
    cb->send = send;
    cb->putData = putData;
    cb->onNewAddress = onNewAddress;
    cb->onAddressSynchronized = onAddressSynchronized;
    cb->onReject = onReject;
    return cb;
}

void c_send(KMessage* Kmessage){
    if(Kmessage != NULL){}
}

void putData(void* client_ptr, KMessage* Kmessage){
    KMsg *kmsg = setMessage(Kmessage);
    char* address = (char*)getAddress(kmsg);
    if(client_ptr == NULL){}
    
    if(getAddressSize(kmsg)==0)
        return;

    if(check_Type(kmsg->Kmessage, "SNAPSHOTRESP", 0) == 0){
        char* key = (char*)getKey(kmsg);
        char* body = (char*)getBody(kmsg);
        printf("Message received on address : %s / Key : %s / Body : %s\n", address, key, body);
        free(key), free(body);
    }
    free(address);
}

void onNewAddress(char* address, uint8_t address_size){
    if(address != NULL && address_size != 0){}
}

void onAddressSynchronized(char* address, uint8_t address_size){
    if(address != NULL && address_size != 0){}
}

void onReject(void* client_ptr){
    Client *client = (Client*)client_ptr;
    int log_size = client->ip_size+1+get_int_len(client->port)+22;
    char log[log_size];
    snprintf(log, log_size, "%s%s%d%s", client->ip, ":", client->port, " join request refused");
    log_srvMsg(client->node->config->log_Path, "KalimaMQ", "Node", ERR, log);
}

ClientCallback* set_callback(){
    return new_ClientCallback(c_send, putData, onNewAddress, onAddressSynchronized, onReject);
}
