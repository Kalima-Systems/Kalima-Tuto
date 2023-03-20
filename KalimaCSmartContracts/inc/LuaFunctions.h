#ifndef LUAFUNCTIONS_H
#define LUAFUNCTIONS_H

#define CLONELIB

#include <math.h>
#include "Node.h"
#include "ContractList.h"

/**
 * @brief Function that will be used in Lua contract to get body from Pointer to KMsg (In contract LuaGetBody(void* kmsg))
 * 
 * @param L Lua state
 * @return 1 
 */
int LuaGetBody(lua_State*L);
/**
 * @brief Function that will be used in Lua contract to get key from Pointer to KMsg (In contract LuaGetKey(void* kmsg))
 * 
 * @param L Lua state
 * @return 1 
 */
int LuaGetKey(lua_State*L);
/**
 * @brief Function that will be used in Lua contract to send message to BlockChain (In contract LuaPutMsg(void* node, string address, int address_size, string key, int key_size, string body, int body_size))
 * 
 * @param L Lua state
 * @return 0 
 */
int LuaPutMsg(lua_State*L);
/**
 * @brief Function that will be used in Lua contract to get string length (In contract LuaStrlen(string str))
 * 
 * @param L Lua state
 * @return 1 
 */
int LuaStrlen(lua_State*L);
/**
 * @brief Function that will be used in Lua contract to print string to Logs (In contract LuaPutLog(void* node, string log_msg))
 * 
 * @param L Lua state
 * @return 0
 */
int LuaPutLog(lua_State*L);

#endif