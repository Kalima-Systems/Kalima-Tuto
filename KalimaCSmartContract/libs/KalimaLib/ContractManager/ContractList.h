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

#include "filewatcher.h"
#include "decrypt.h"
#include "LuaScriptHandler.h"
#include "../KalimaCUtil/logger.h"

/**
 * @brief ContractList structure
 * 
 */
typedef struct ContractList ContractList;
struct ContractList
{
    uint8_t iscrypted; /**< Act as boolean to see if contracts in ContractList are crypted (1 : yes / 0 : no) */
    char* Blockchain_path; /**< Path to add at start of Lua's address */
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
 * @param name Lua's script_name
 * @param address Lua's address
 * @return Pointer to Lua
 */
Lua* new_Lua(char* filename, char* name, char* address);
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
 * @param Blockchain_path BlockChain's path
 * @param iscrypted Acts as boolean to check if contracts are crypted
 * @return Pointer to ContractList 
 */
ContractList* new_ContractList(char* path, char* Blockchain_path, uint8_t iscrypted);
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
 * @brief Use contract matching the BlockChain's address
 * 
 * @param list Pointer to ContractList
 * @param address Address string
 * @param ptr1 Pointer to KMsg
 * @param ptr2 Pointer to Node
 */
void use_contract(ContractList* list, char* address, void* ptr1, void* ptr2);

/**
 * @brief Print a Lua contract (script name / address)
 * 
 * @param x Lua contract
 */
void print_lua_script(Lua*x);
/**
 * @brief Print a Lua list (script_name1->script_name2 ...)
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

#endif