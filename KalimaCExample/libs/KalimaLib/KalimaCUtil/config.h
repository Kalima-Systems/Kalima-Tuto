#ifndef CONFIG_h
#define CONFIG_h

#include <stdint.h>
#include "LinkedList.h"

#define MAXLINE 200

typedef struct Notary Notary;
struct Notary
{
    uint8_t* ip;
    uint8_t ip_size;
    uint16_t port;
};

typedef struct Config Config;
struct Config
{
    char *Ledger_Name;
    uint8_t Ledger_size;
    char *Node_Name;
    uint8_t Node_size;
    uint16_t Port;
    List *Notaries;
    int32_t watchdog;
    char *Files_Path;
    uint8_t FilesPath_size;
    char *Serial_ID;
    uint8_t SerialId_size;
    char *private_key;
    uint8_t private_key_size;
    char *public_key;
    uint8_t public_key_size;
    char *blockchain_public_key;
    uint8_t blockchain_public_key_size;
};

Config *load_config(char* file);
void config_init(Config *config);
void check_line(Config* config, char* str);
void print_notary(void* v);

#endif