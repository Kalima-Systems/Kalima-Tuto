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
    Client *client = (Client*)client_ptr;
    KMsg *kmsg = setMessage(Kmessage);

    if(getAddressSize(kmsg)==0)
        return;

    if(check_Type(kmsg->Kmessage, "SNAPSHOTRESP", 0) == 0){
        void* kmsg_ptr = (void*)kmsg;
        void* node_ptr = (void*)client->node;
        char* address = (char*)getAddress(kmsg);

        ContractList *contract_list = (ContractList*)client->node->contract_list;
        if(contract_list != NULL){
            log_srvMsg(client->node->config->Files_Path, "Contract", "Manager", INFO, "data received");
            for(int i=0;i<nb_of_elements(contract_list->List);i++){
                Lua* lua_script = (Lua*)(list_get_element(contract_list->List, i)->data);
                if(strncmp(address,lua_script->address,getAddressSize(kmsg))==0){
                    log_srvMsg(client->node->config->Files_Path, "Contract", "Manager", INFO, "contract will be used");
                    use_contract(contract_list, lua_script->address, kmsg_ptr, node_ptr);
                    log_srvMsg(client->node->config->Files_Path, "Contract", "Manager", INFO, "contract finished being used");
                }
            }
        }
        free(address);
    }
    free_KMsg(kmsg);
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
    log_srvMsg(client->node->config->Files_Path, "KalimaMQ", "Node", ERR, log);
}

ClientCallback* set_callback(){
    return new_ClientCallback(c_send, putData, onNewAddress, onAddressSynchronized, onReject);
}
