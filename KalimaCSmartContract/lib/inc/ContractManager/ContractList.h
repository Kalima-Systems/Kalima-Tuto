#ifndef CONTRACTLIST_H
#define CONTRACTLIST_H

/**
 * @file ContractList.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Main ContractManager handler
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
#include <dirent.h>
#include <pthread.h>
#include <sys/stat.h>
#include "LinkedList.h"
#include "Lua/lua.h"
#include "Lua/luaj.h"
#include "Lua/lualib.h"
#include "Lua/lauxlib.h"
#include "filewatcher.h"
#include "decrypt.h"
#include "logger.h"

/**
 * @brief Structure for Lua smartcontracts informations
 * 
 */
typedef struct Lua Lua;
struct Lua
{
    char* filepath; /**< SmartContract's path + file's name (ex : /home/contract/contract.lua) */
    char* filename; /**< File's name (ex : contract.lua) */
    uint8_t isvalid; /**< Act as a boolean to see if contract's signature is good (if the contract is crypted) */
    unsigned char* decrypted_content; /**< Crypted contract decrypted's content */
    uint16_t decrypted_content_size; /**< Crypted contract decrypted's content size */
    lua_State* L; /**< Lua state (Necessary to use Lua's library) */
};

/**
 * @brief ContractList structure
 * 
 */
typedef struct ContractList ContractList;
struct ContractList
{
    uint8_t iscrypted; /**< Act as boolean to see if contracts in ContractList are crypted (1 : yes / 0 : no) */
    char* Contract_path; /**< Path to add at start of Lua's script_name and for filewatcher */
    List* List; /**< List of pointers to Lua */
    pthread_mutex_t ListLock; /**< Mutex to protect the List (since there is a thread to watch directory) */
    pthread_t WatcherThread; /**< Thread to watch directory */
    int fd;
};

/**
 * @brief Lua initializer
 * 
 * @param filename Lua's filename
 * @param name Lua's filepath
 * @return Pointer to Lua
 */
Lua* new_Lua(char* filename, char* filepath);
/**
 * @brief Decrypt Lua's contract if check_signature_SHA256() returns 1
 * 
 * @param lua Pointer to Lua
 * @param path Lua contract path
 * @param signature Signature from Blockchain
 * @param aesKey Aes key from BlockChain
 * @param aesIV Aes IV from BlockChain
 */
void decrypt_Lua_script(Lua* lua, char* path, char* signature, char* aesKey, char* aesIV);

/**
 * @brief Create new ContractList
 * 
 * @param path ContractList's path
 * @param iscrypted Acts as boolean to check if contracts are crypted
 * @return Pointer to ContractList 
 */
ContractList* new_ContractList(char* path, uint8_t iscrypted);
/**
 * @brief At start check LuaScripts directory and add every lua scripts to Lua List
 * 
 * @param list Lua List
 * @return 1 -- At least 1 contract added ; 0 -- No contract
 */
int set_Lua_List(ContractList *list);
/**
 * @brief Thread to watch directory for events
 * 
 * @param l Pointer to ContractList
 * @return void* 
 */
void *contract_watcher(void* l);
/**
 * @brief Get a Lua from ContractList matching filename and load it
 * 
 * @param list Pointer to ContractList
 * @param filename Filemane string
 * @return Lua contract
 */
Lua* load_Contract(ContractList* list, char* filename);

/**
 * @brief Print a Lua contract (script name / address)
 * 
 * @param x Lua contract
 */
void print_lua_script(Lua*x);
/**
 * @brief Print a Lua list (filepath1->filepath2 ...)
 * 
 * @param list Lua List
 */
void print_lua_list(List*list);
/**
 * @brief Free a Lua list
 * 
 * @param element Pointer to element
 */
void list_lua_free(void* element);
/**
 * @brief Lua compare function to use list_get_index()
 * 
 * @param x Path
 * @param y Pointer to Lua
 * @return strcmp
 */
int list_lua_cmp(void *x, void* y);
/**
 * @brief Free a ContractList
 * 
 * @param list Pointer to ContractList
 */
void free_ContractList(ContractList* list);
/**
 * @brief Curl request to get smart contracts
 * 
 * @param url Server url
 * @param filename Filename of the file to get
 * @param contract_path local contract path
 */
void curl_req(char* url, char* filename, char* contract_path);

#endif