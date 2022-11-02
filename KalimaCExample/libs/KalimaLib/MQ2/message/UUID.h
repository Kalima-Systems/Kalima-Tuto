#ifndef UUID_h
#define UUID_h

/**
 * @file UUID.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief Get UUID from MAC Address
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "DevID.h"
#include "../../KalimaCUtil/BytesArray.h"

/**
 * @brief UUID size
 * 
 */
#define UUID_SIZE 36

/**
 * @brief Define Long Hexadecimal format depending on architecture
 * 
 */
# if __x86_64__
#  define LONGHEX_A	"lx"
# else
#  define LONGHEX_A	"llx"
# endif

/**
 * @brief UUID structure
 * 
 */
typedef struct UUID UUID;
struct UUID
{
    int64_t Most_Sig_Bits; /**< UUID's most significant bits */
    int64_t Least_Sig_Bits;/**< UUID's least significant bits */
};

/**
 * @brief Create UUID from bytes
 * 
 * @param data Bytes that will be digested and used to create a UUID
 * @param data_size Bytes size
 * @return UUID 
 */
UUID name_UUID_from_Bytes(char* data, uint8_t data_size);

/**
 * @brief Get the most significant bits from UUID
 * 
 * @param uuid UUID
 * @return Most significant bits
 */
int64_t get_Most_Sig_Bits(UUID uuid);
/**
 * @brief Get the least significant bits from UUID
 * 
 * @param uuid UUID
 * @return Least significant bits
 */
int64_t get_Least_Sig_Bits(UUID uuid);
/**
 * @brief Get the UUID's version
 * 
 * @param uuid UUID
 * @return Version
 */
int get_Version(UUID uuid);
/**
 * @brief Get the UUID's variant
 * 
 * @param uuid UUID
 * @return Variant
 */
int get_Variant(UUID uuid);
/**
 * @brief Get the UUID's timestamp
 * 
 * @param uuid UUID
 * @return Timestamp
 */
int64_t get_Timestamp(UUID uuid);
/**
 * @brief Get the UUID's clock sequence
 * 
 * @param uuid UUID
 * @return Clock sequence
 */
int get_ClockSequence(UUID uuid);
/**
 * @brief Get the UUID's node
 * 
 * @param uuid UUID
 * @return UUID's node
 */
int64_t get_Node(UUID uuid);
/**
 * @brief Get the UUID's Hashcode
 * 
 * @param uuid UUID
 * @return Hashcode
 */
int get_HashCode(UUID uuid);
/**
 * @brief Get UUID as a string
 * 
 * @param uuid UUID
 * @param uuid_out UUID as a string
 */
void uuid_to_String(UUID uuid, char* uuid_out);
/**
 * @brief Creates UUID and output UUID as a string
 * 
 * @param uuid_out UUID as a string
 */
void uuid_String(char* uuid_out);
/**
 * @brief Creates random UUID and output UUID as a string from random MAC Address
 * 
 * @param size UUID's size
 * @return UUID as a string
 */
char* random_uuid(uint8_t size);

#endif