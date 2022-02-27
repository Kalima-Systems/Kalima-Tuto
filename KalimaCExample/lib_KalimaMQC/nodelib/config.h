#ifndef CONFIG_h
#define CONFIG_h

#include <stdint.h>

#define MAXLINE 100
#define MAX_NOTARIES 10

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
    Notary Notaries[MAX_NOTARIES];
    uint8_t Nb_Notaries;
    char *Files_Path;
    uint8_t FilesPath_size;
    char *Serial_ID;
    uint8_t SerialId_size;
};

Config load_config(Config config, char* file);
Config check_line(Config config, char* str);

#endif