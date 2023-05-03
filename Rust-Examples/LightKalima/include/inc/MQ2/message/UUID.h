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
#include <stdbool.h>
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

# if __APPLE__
// START OF IOS FUNCTIONS
struct uuuid{
    unsigned char bytes[16];
};

/**
 * Set uuid to the null_uuid.
 */
void uuid0_generate(struct uuuid *res);

/**
 * Generate an uuid of version 4 ( Random ) into res.
 * @note res will be the null_uuid on failure.
 */
void uuid4_generate(struct uuuid *res);

/**
 * Return the type of the provided uuid.
 *
 * @return 0 if it is the null-uuid
 *         1 MAC address & date-time
 *         2 DCE Security
 *         3 MD5 hash & namespace
 *         4 Random
 *         5 SHA-1 hash & namespace
 *
 *         -1 on an invalid uuid.
 */
int uuid_type(struct uuuid *id);

/**
 * Converts an uuid to string.
 * @param id uuid to convert.
 * @param out pointer to char-buffer where to write uuid, uuid is NOT 0-terminated
 *            and is expected to be at least 36 bytes.
 * @return out
 */
char *uuid_to_string(struct uuuid *id, char *out);

/**
 * Convert a string to an uuid.
 * @param str to convert.
 * @param out uuid to parse to.
 * @return true on success.
 */
bool uuid_from_string(const unsigned char *str, struct uuuid *out);

/**
 * Copy uuid from src to dst.
 */
void uuuid_copy(const struct uuuid *src, struct uuuid *dst);
// END OF IOS FUNCTIONS
#endif

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
 * @return On success : 1 @n
 *         On failure : -1
 */
int8_t uuid_to_String(UUID uuid, char uuid_out[MACAddr_size]);
/**
 * @brief Creates UUID and output UUID as a string
 * 
 * @param uuid_out UUID as a string
 * @return On success : 1 @n
 *         On failure : -1
 */
int8_t uuid_String(char uuid_out[MACAddr_size]);
/**
 * @brief Creates random UUID and output UUID as a string from random MAC Address
 * 
 * @return On success : random UUID string @n
 *         On failure : NULL
 */
char* random_uuid();

#endif