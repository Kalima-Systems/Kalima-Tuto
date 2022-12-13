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
    ContractList *contract_list = (ContractList*)client->node->contract_list;
    char* address = (char*)getAddress(kmsg);

    if(getAddressSize(kmsg)==0)
        return;
    
    if(contract_list->iscrypted == 1){
        if(strncmp(address,"/Kalima_Scripts",getAddressSize(kmsg))==0){
            char* key = (char*)getKey(kmsg);
            char *file;
            set_String(key, strlen(key), (void**)&file);
            strtok(file, ".");
            char* filetype = strtok(NULL, "\0");
            if(key != NULL && filetype != NULL && strncmp(filetype, "lua", 3) == 0){
                char* url = (char*)getProp(kmsg, "downloadURL");
                log_srvMsg(client->node->config->log_Path, "Contract", "Manager", ERR, "Curl request ...");
                curl_req(url, key ,contract_list->Contract_path);
                log_srvMsg(client->node->config->log_Path, "Contract", "Manager", ERR, "Curl request done");
                free(url);
                int i;
                for(i=0;i<nb_of_elements(contract_list->List);i++){
                    Lua* lua_script = (Lua*)(list_get_element(contract_list->List, i)->data);
                    int contract_log_size = 19+strlen(key)+21+strlen(lua_script->filename);
                    char contract_log[contract_log_size];
                    snprintf(contract_log, contract_log_size, "%s%s%s%s", "remote filename : ", key, " / local filename : ", lua_script->filename);
                    log_srvMsg(client->node->config->log_Path, "Contract", "Manager", DEBUG, contract_log);
                    if(strncmp(lua_script->filename,key,strlen(key))==0){
                        log_srvMsg(client->node->config->log_Path, "Contract", "Manager", DEBUG, "SmartContract is on local system");
                        char* signature = (char*)getProp(kmsg, "signature");
                        char* aesKey = (char*)getProp(kmsg, "aesKey");
                        char* aesIV = (char*)getProp(kmsg, "aesIV");
                        if(signature == NULL || aesKey == NULL || aesIV == NULL){
                            log_srvMsg(client->node->config->log_Path, "Contract", "Manager", ERR, "Error getting aes infos from props");
                            free(key), free(address);
                            return;
                        }
                        log_srvMsg(client->node->config->log_Path, "Contract", "Manager", DEBUG, "Decrypt SmartContract");
                        decrypt_Lua_script(lua_script, lua_script->filepath, signature, aesKey, aesIV);
                        free(signature), free(aesKey), free(aesIV);
                    }
                }
            }
            free(key), free(file);
        }
    }

    if(check_Type(kmsg->Kmessage, "SNAPSHOTRESP", 0) == 0){
        void* kmsg_ptr = (void*)kmsg;
        void* node_ptr = (void*)client->node;

        if(contract_list != NULL){
            log_srvMsg(client->node->config->log_Path, "Contract", "Manager", INFO, "data received");
            if(strncmp(address,"/sensors",getAddressSize(kmsg))==0){
                log_srvMsg(client->node->config->log_Path, "Contract", "Manager", INFO, "Using contract sensors.lua");
                Lua* Lua_contract = load_Contract(contract_list, "sensors.lua");
                if(Lua_contract == NULL){
                    log_srvMsg(client->node->config->log_Path, "Contract", "Manager", ERR, "Error loading contract");
                    free(address);
                    return;
                }
                lua_getglobal(Lua_contract->L,"main");
                lua_pushcfunction(Lua_contract->L,LuaGetBody);
                lua_setglobal(Lua_contract->L, "LuaGetBody");
                lua_pushcfunction(Lua_contract->L,LuaGetKey);
                lua_setglobal(Lua_contract->L, "LuaGetKey");
                lua_pushcfunction(Lua_contract->L,LuaPutMsg);
                lua_setglobal(Lua_contract->L, "LuaPutMsg");
                lua_pushcfunction(Lua_contract->L,LuaPutLog);
                lua_setglobal(Lua_contract->L, "LuaPutLog");
                lua_pushcfunction(Lua_contract->L,LuaStrlen);
                lua_setglobal(Lua_contract->L, "LuaStrlen");
                lua_pushlightuserdata(Lua_contract->L,kmsg_ptr);
                lua_pushlightuserdata(Lua_contract->L,node_ptr);
                lua_pcall(Lua_contract->L, 2, 0, 0);
                log_srvMsg(client->node->config->log_Path, "Contract", "Manager", INFO, "Finished using contract");
            }
        } 
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
