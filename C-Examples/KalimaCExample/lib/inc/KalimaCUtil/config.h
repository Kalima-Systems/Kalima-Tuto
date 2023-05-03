#ifndef CONFIG_h
#define CONFIG_h

/**
 * @file config.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Reads config files and puts data collected in Config structure
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>
#include "LinkedList.h"
#include "BytesArray.h"

/**
 * @brief Max size of a line in config file
 * 
 */
#define MAXLINE 200

/**
 * @brief Notary structure
 * @details To connect to a Kalima Blockchain, you need to connect to multiple Notary nodes\n
 *          To facilitate reading and using notaries from config files, each IP address / port is put in a structure to add to a List later
 */
typedef struct Notary Notary;
struct Notary
{
    uint8_t* ip; /**< String of the Notary's IP address */
    uint8_t ip_size; /**< Size of the IP string */
    uint16_t port; /**< Port of the Notary */
};

/**
 * @brief Config structure
 * @details Contains all usefull data collected from config file
 */
typedef struct Config Config;
struct Config
{
    /*@}*/
    /**
     * @name Data from config file
     */
    /*@{*/
    char *Ledger_Name; /**< String of the Ledger's name */
    char *Node_Name; /**< String of the Node's name */
    uint16_t Port; /**< Server port if the node is also a server */
    List *Notaries; /**< List of Notary */
    int32_t watchdog; /**< Watchdog (default : -1) */
    char *Files_Path; /**< Files path */
    char *log_Path; /**< Logs path */
    char *DevID_Path; /**< DevId path */
    char *RSA_Path; /**< RSA path */
    char *Serial_ID; /**< String of the SerialID*/
    char *private_key; /**< String of the private key path */
    char *public_key; /**< String of the public key path */
    char *blockchain_public_key; /**< String of the blockchain public key path */
    char *contract_user;
    /*@}*/
    /**
     * @name Size of data from config file
     */
    /*@{*/
    uint8_t Ledger_size; /**< Size of the Ledger's name */
    uint8_t Node_size; /**< Size of the Node's name */
    uint8_t FilesPath_size; /**< Logs files path size */
    uint8_t LogPath_size; /**< Logs files path size */
    uint8_t DevIDPath_size; /**< DevID files path size */
    uint8_t RSAPath_size; /**< RSA files path size */
    uint8_t SerialId_size; /**< Size of the SerialID */
    uint8_t private_key_size; /**< Size of the private key path */
    uint8_t public_key_size; /**< Size of the public key path */
    uint8_t blockchain_public_key_size; /**< Size of the blockchain public key path */
    uint8_t contract_user_size;
};

/**
 * @brief Main Config.h function
 * @details Load data from config file into Config pointer
 * 
 * @param file File name (+path if necessary)
 * @return pointer to Config
 */
Config *load_config(char* file);

/// @private
/**
 * @brief Print Notary
 * 
 * @param v pointer to Notary
 */
void print_notary(void* v);
/**
 * @brief Free config structure
 * 
 * @param config Pointer to config to free
 */
void free_config(Config *config);

#endif