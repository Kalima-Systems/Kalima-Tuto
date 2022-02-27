#ifndef UUID_h
#define UUID_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "DevID.h"

#define MD5_size 16
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
#define UUID_SIZE 36

typedef struct UUID UUID;
struct UUID
{
    long Most_Sig_Bits;
    long Least_Sig_Bits;
};

uint8_t* md5(uint8_t *initial_msg, size_t initial_len);
UUID new_UUID(uint8_t* data, uint8_t data_size);
UUID name_UUID_from_Bytes(char* data, uint8_t data_size);

long get_Most_Sig_Bits(UUID uuid);
long get_Least_Sig_Bits(UUID uuid);
int get_Version(UUID uuid);
int get_Variant(UUID uuid);
long get_Timestamp(UUID uuid);
int get_ClockSequence(UUID uuid);
long get_Node(UUID uuid);
int get_HashCode(UUID uuid);
void padHex( long l, int n, char* out );
void uuid_to_String(UUID uuid, char* uuid_out);
void uuid_String(char* uuid_out);
void random_uuid(char* random_uuid, uint8_t size);

#endif