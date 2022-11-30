#include "LuaFunctions.h"

int LuaGetBody(lua_State*L){

    void* Kmsg_ptr = lua_touserdata(L,1);
    KMsg* msg = (KMsg*) Kmsg_ptr;
    char* body = (char*)getBody(msg);

    lua_pushstring(L,body);
    free(body);
    return 1;
}

int LuaGetKey(lua_State*L){

    void* Kmsg_ptr = lua_touserdata(L,1);
    KMsg* msg = (KMsg*) Kmsg_ptr;
    char* key = (char*)getKey(msg);

    lua_pushstring(L,key);
    free(key);
    return 1;
}

int LuaPutMsg(lua_State*L){

    void* node_ptr = lua_touserdata(L,1);
    Node* node = (Node*) node_ptr;
    char* address = (char*)lua_tostring(L,2);
    uint8_t address_size = lua_tonumber(L,3);
    char* key = (char*)lua_tostring(L,4);
    uint8_t key_size = lua_tonumber(L,5);
    char* body = (char*)lua_tostring(L,6);
    uint16_t body_size = lua_tonumber(L,7);
    log_srvMsg(node->config->Files_Path, "KalimaMQ", "Node", INFO, "Sending from contract to notary 1");
    put_msg_default(node->clone, address, address_size, key, key_size, body, body_size);
    log_srvMsg(node->config->Files_Path, "KalimaMQ", "Node", INFO, "Sending from contract to notary 2");
    return 0;
}

int LuaStrlen(lua_State*L){
    char* string = (char*)lua_tostring(L,1);
    int size = (int)strlen(string);
    lua_pushinteger(L, size);
    return 1;
}

int LuaPutLog(lua_State*L){
    void* node_ptr = lua_touserdata(L,1);
    Node* node = (Node*) node_ptr;
    char* log = (char*)lua_tostring(L,2);
    log_srvMsg(node->config->Files_Path, "Main", "Log", INFO, log);
    return 0;
}