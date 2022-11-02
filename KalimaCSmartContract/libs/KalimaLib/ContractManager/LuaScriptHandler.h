#ifndef LUASCRIPTHANDLER_H
#define LUASCRIPTHANDLER_H

/**
 * @file LuaScriptHandler.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Will handle Lua SmartContracts
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <dirent.h>
#include "../KalimaCUtil/LinkedList.h"
#include "../KalimaCUtil/BytesArray.h"
#include "../MQ2/nodelib/Node.h"
#include "../NodeLib/clone.h"
#include "lib_Lua/include/lua/lua.h"
#include "lib_Lua/include/lua/luaj.h"
#include "lib_Lua/include/lua/lualib.h"
#include "lib_Lua/include/lua/lauxlib.h"
#include "filewatcher.h"
#include "decrypt.h"

/**
 * @brief Structure for Lua smartcontracts informations
 * 
 */
typedef struct Lua Lua;
struct Lua
{
    char* script_name; /**< SmartContract's path + file's name (ex : /home/contract/contract.lua) */
    char* filename; /**< File's name (ex : contract.lua) */
    char* address; /**< BlockChain's address you want your smartcontract to watch (ex : /demo/contract.lua) */
    uint8_t isvalid; /**< Act as a boolean to see if contract's signature is good (if the contract is crypted) */
    unsigned char* decrypted_content; /**< Crypted contract decrypted's content */
    uint16_t decrypted_content_size; /**< Crypted contract decrypted's content size */
    lua_State* L; /**< Lua state (Necessary to use Lua's library) */
};

/**
 * @brief Reads a Lua contract and put the functions's names that will be used in main Lua function in a List
 * 
 * @param lua Pointer to Lua
 * @return Pointer to List containing functions' names that will be used
 */
List* get_functions(Lua* lua);
/**
 * @brief Function that will be used in Lua contract to add function's name to List
 * 
 * @param L Lua state
 * @return 1 
 */
int add_function(lua_State*L);
/**
 * @brief Will check List's functions' names to see if there are matching functions available
 * 
 * @param lua Pointer to Lua
 * @param function_list Pointer to function's List
 */
void check_functions(Lua* lua, List* function_list);

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
 * @brief Function that will be used in Lua contract to get temperature from Kerlink's payload (In contract LuaGetTemperature(string payload))
 * 
 * @param L Lua state
 * @return 1 
 */
int LuaGetTemperature(lua_State*L);
/**
 * @brief Function that will be used in Lua contract to get humidity from Kerlink's payload (In contract LuaGetHumidity(string payload))
 * 
 * @param L Lua state
 * @return 1 
 */
int LuaGetHumidity(lua_State*L);
/**
 * @brief Function that will be used in Lua contract to get VOC from Kerlink's payload (In contract LuaGetVOC(string payload))
 * 
 * @param L Lua state
 * @return 1 
 */
int LuaGetVOC(lua_State*L);
/**
 * @brief Function that will be used in Lua contract to get CO2 from Kerlink's payload (In contract LuaGetCO2(string payload))
 * 
 * @param L Lua state
 * @return 1 
 */
int LuaGetCO2(lua_State*L);
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