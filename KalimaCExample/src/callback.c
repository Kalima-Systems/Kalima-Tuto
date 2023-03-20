#include "callback.h"

ClientCallback* new_ClientCallback(ClientCallback_send send, ClientCallback_onNewAddress onNewAddress, ClientCallback_onAddressSynchronized onAddressSynchronized, ClientCallback_onReject onReject){
    ClientCallback* cb = malloc(sizeof(ClientCallback));
    if(cb == NULL){
      return NULL;
    }
    cb->send = send;
    cb->onNewAddress = onNewAddress;
    cb->onAddressSynchronized = onAddressSynchronized;
    cb->onReject = onReject;
    return cb;
}

MemCacheCallback* new_MemCacheCallback(MemCacheCallback_putData putData, MemCacheCallback_removeData removeData, MemCacheCallback_getAddress getAddress){
    MemCacheCallback* mb = malloc(sizeof(MemCacheCallback));
    if(mb == NULL) return NULL;
    mb->putData = putData;
    mb->removeData = removeData;
    mb->getAddress = getAddress;
    return mb;
}

void c_send(KMessage* Kmessage){
    if(Kmessage != NULL){}
}

void onNewAddress(void* node_ptr, char* address, uint8_t address_size){
    Node* node = (Node*)node_ptr;
    if(node!=NULL && address != NULL && address_size != 0){}
}

void onAddressSynchronized(void* node_ptr, char* address, uint8_t address_size){
    Node* node = (Node*)node_ptr;
    if(node!=NULL && address != NULL && address_size != 0){
        if(strncmp(address, "/sensors", address_size)==0){
            MemCacheCallback* memcacheCallback = set_memcacheCallback();
            add_MemCacheCallback(node->clone, memcacheCallback);
        }
        
    }
}

void onReject(void* client_ptr){
    Client *client = (Client*)client_ptr;
    int log_size = client->ip_size+1+get_int_len(client->port)+22;
    char log[log_size];
    snprintf(log, log_size, "%s%s%d%s", client->ip, ":", client->port, " join request refused");
    log_srvMsg(client->node->config->log_Path, "KalimaMQ", "Node", ERR, log);
}

void putData(void* clone_ptr, KMessage* Kmessage){
    Clone* clone = (Clone*)clone_ptr;
    KMsg *kmsg = setMessage(Kmessage);
    if(clone==NULL || kmsg==NULL || getAddressSize(kmsg)==0) return;
    char* address = (char*)getAddress(kmsg);

    char* key = (char*)getKey(kmsg);
    char* body = (char*)getBody(kmsg);
    printf("Message added on address : %s / Key : %s / Body : %s\n", address, key, body);
    free(key), free(body), free(address);
}

void removeData(void* clone_ptr, KMessage* Kmessage){
    Clone* clone = (Clone*)clone_ptr;
    KMsg *kmsg = setMessage(Kmessage);
    if(clone==NULL || kmsg==NULL || getAddressSize(kmsg)==0) return;
    char* address = (char*)getAddress(kmsg);

    char* key = (char*)getKey(kmsg);
    char* body = (char*)getBody(kmsg);
    printf("Message removed on address : %s / Key : %s / Body : %s\n", address, key, body);
    free(key), free(body), free(address);
}

char* mc_getAddress(){
    return "/sensors";
}

ClientCallback* set_clientCallback(){
    return new_ClientCallback(c_send, onNewAddress, onAddressSynchronized, onReject);
}

MemCacheCallback* set_memcacheCallback(){
    return new_MemCacheCallback(putData, removeData, mc_getAddress);
}