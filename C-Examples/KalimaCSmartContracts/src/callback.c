#include "callback.h"

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
        if(strncmp(address, "/Kalima_Contracts", 17)==0){
            ContractList *contract_list = (ContractList*)node->contract_list;
            MemCache* memcache = getMemCache(node->clone, address, address_size);
            SkipListNode_t *kvmap = SkipListGetFirst( memcache->kvmap );
            for ( ; kvmap; kvmap=kvmap->forward[0] ) {
                KMessage* msg = build((unsigned char*)((KeyValueObj *)kvmap->key)->value+4);
                KMsg *kmsg = setMessage(msg);
                char* key = (char*)((KeyValueObj *)kvmap->key)->key;
                int key_size = ((KeyValueObj *)kvmap->key)->key_size;
                char* file;
                set_String(key, key_size, (void**)&file);
                strtok(file, ".");
                char* filetype = strtok(NULL, "\0");
                if(filetype != NULL && strncmp(filetype, "lua", 3) == 0){
                    char* url = (char*)getProp(kmsg, "downloadURL");
                    log_srvMsg(node->config->log_Path, "Contract", "Manager", ERR, "Curl request ...");
                    curl_req(url, key, contract_list->Contract_path);
                    log_srvMsg(node->config->log_Path, "Contract", "Manager", ERR, "Curl request done");
                    free(url);
                    int i;
                    for(i=0;i<nb_of_elements(contract_list->List);i++){
                        Lua* lua_script = (Lua*)(list_get_element(contract_list->List, i)->data);
                        int contract_log_size = 19+strlen(key)+21+strlen(lua_script->filename);
                        char contract_log[contract_log_size];
                        snprintf(contract_log, contract_log_size, "%s%s%s%s", "remote filename : ", key, " / local filename : ", lua_script->filename);
                        log_srvMsg(node->config->log_Path, "Contract", "Manager", DEBUG, contract_log);
                        if(strncmp(lua_script->filename,key,key_size)==0){
                            log_srvMsg(node->config->log_Path, "Contract", "Manager", DEBUG, "SmartContract is on local system");
                            char* signature = (char*)getProp(kmsg, "signature");
                            char* aesKey = (char*)getProp(kmsg, "aesKey");
                            char* aesIV = (char*)getProp(kmsg, "aesIV");
                            if(signature == NULL || aesKey == NULL || aesIV == NULL){
                                log_srvMsg(node->config->log_Path, "Contract", "Manager", ERR, "Error getting aes infos from props");
                                free(key), free(address);
                                return;
                            }
                            log_srvMsg(node->config->log_Path, "Contract", "Manager", DEBUG, "Decrypt SmartContract");
                            decrypt_Lua_script(lua_script, lua_script->filepath, signature, aesKey, aesIV);
                            free(signature), free(aesKey), free(aesIV);
                        }
                    }
                }
                free(file);
            }
        }
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
    ContractList *contract_list = (ContractList*)clone->node->contract_list;
    KMsg *kmsg = setMessage(Kmessage);
    if(clone==NULL || kmsg==NULL || getAddressSize(kmsg)==0) return;
    char* address = (char*)getAddress(kmsg);

    char* key = (char*)getKey(kmsg);
    char* body = (char*)getBody(kmsg);
    printf("Message added on address : %s / Key : %s / Body : %s\n", address, key, body);

    if(contract_list != NULL){
        log_srvMsg(clone->node->config->log_Path, "Contract", "Manager", INFO, "Using contract sensors.lua");
        Lua* Lua_contract = load_Contract(contract_list, "sensors.lua");
        if(Lua_contract == NULL){free(address); return;}
        lua_getglobal(Lua_contract->L,"main");
        lua_pushcfunction(Lua_contract->L,LuaGetBody);
        lua_setglobal(Lua_contract->L, "LuaGetBody");
        lua_pushcfunction(Lua_contract->L,LuaGetKey);
        lua_setglobal(Lua_contract->L, "LuaGetKey");
        lua_pushcfunction(Lua_contract->L,LuaPutMsg);
        lua_setglobal(Lua_contract->L, "LuaPutMsg");
        lua_pushcfunction(Lua_contract->L,LuaPutLog);
        lua_setglobal(Lua_contract->L, "LuaPutLog");
        lua_pushcfunction(Lua_contract->L,LuaStrLen);
        lua_setglobal(Lua_contract->L, "LuaStrLen");
        lua_pushlightuserdata(Lua_contract->L,(void*)kmsg);
        lua_pushlightuserdata(Lua_contract->L,(void*)clone->node);
        lua_pcall(Lua_contract->L, 2, 0, 0);
        log_srvMsg(clone->node->config->log_Path, "Contract", "Manager", INFO, "Finished using contract");
    }
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

ClientCallback* set_clientCallback(){
    return new_ClientCallback(c_send, onNewAddress, onAddressSynchronized, onReject);
}

MemCacheCallback* set_memcacheCallback(){
    return new_MemCacheCallback(putData, removeData, "/sensors");
}