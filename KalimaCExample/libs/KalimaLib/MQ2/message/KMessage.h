#ifndef KMESSAGE_H
#define KMESSAGE_H

#include <stdarg.h>
#include <stdint.h>
#include "Header.h"
#include "../../KalimaCUtil/aes.h"

typedef struct KMessage KMessage;
struct KMessage{
    struct Header *header;
	unsigned char** frames;
};

struct KMessage* KMessage_new();
struct KMessage* create_KMessage(unsigned char* frames, int32_t nbFrames, int32_t* sizes);
struct KMessage* create_KMessage2(int32_t nbFrames, unsigned char* frame1, int32_t size1, ...);
void construct_Header(struct KMessage*, int32_t nbFrames, int32_t* sizes);
struct Header* get_Header(struct KMessage*);
void set_Header(struct KMessage*, struct Header*);
unsigned char** get_Frames(struct KMessage*);
unsigned char* get_Frame(struct KMessage*, int32_t i);
void set_Frames(struct KMessage*, unsigned char* frames, int32_t nbFrames, int32_t* sizes);
unsigned char *get_DEVID(struct KMessage*);
int32_t get_Framesize(struct KMessage*, int32_t i);
int32_t get_DEVIDSize(struct KMessage*);
unsigned char* get_Frames_Bytes(struct KMessage*);
int32_t get_Frames_Bytes_Size(struct KMessage*);
unsigned char* get_Bytes(struct KMessage*);
int32_t get_Bytes_Size(struct KMessage*);
unsigned char* get_KMessage_Bytes(struct KMessage*);
int32_t get_KMessage_Bytes_Size(struct KMessage*);
/*unsigned char* getEncryptedBytes();
static unsigned char* encrypt();
static KMessage decrypt();*/
struct KMessage* build(unsigned char *data);
unsigned char encode_Type(int32_t mestype);
unsigned char decode_Type(unsigned char bhead);
unsigned char get_Type(struct KMessage*);
void set_Type(struct KMessage* Kmessage, unsigned char type);
int32_t get_Min_ver(int32_t ver);
int32_t get_Maj_ver(int32_t ver);
int32_t get_Ver(unsigned char bhead);
/*static bool sameVersion(unsigned char bhead);*/
int32_t get_Min_ver_KM(struct KMessage*);
int32_t get_Maj_ver_KM(struct KMessage*);
/*bool equals(KMessage o);*/

unsigned char* create_encrypted_message(unsigned char* msg_to_encrypt, int32_t size, uint8_t* key, uint8_t* iv);
void print_Header(struct Header *header);
void print_KMessage(struct KMessage *kMessage);

static const unsigned char VOTEREQ = 0b0000;
static const unsigned char VOTERESP = 0b0001;
static const unsigned char VOTEAYT = 0b0010;
static const unsigned char VOTEIHY = 0b0011;
static const unsigned char VOTERES = 0b0100;
static const unsigned char ADMIN = 0b0101;
static const unsigned char AYT = 0b0110;
static const unsigned char IHY = 0b0111;
static const unsigned char PUB = 0b1000;
static const unsigned char SUB = 0b1001;
static const unsigned char SNAPSHOTREQ = 0b1010;
static const unsigned char NODEACTION = 0b1011;
static const unsigned char REQUEST_PUB = 0b1100;
static const unsigned char SNAPSHOTRESP = 0b1101;
static const unsigned char LEADER_PUB = 0b1110;

static const unsigned char JOIN = 0b1111;
static const unsigned char JOIN_REQ = 0x00;
static const unsigned char JOIN_RES = 0x01;

static const uint8_t FRAME_PUBLIC_KEY = 4;
static const uint8_t FRAME_DEVID = 0;
static const uint8_t FRAME_TYPE = 1;
static const uint8_t FRAME_ADDRESS = 2;
static const uint8_t FRAME_SERIALID = 2;
static const uint8_t FRAME_SUB_TYPE = 3;
static const uint8_t FRAME_SNASPHOT_TYPE = 3;
static const uint8_t FRAME_SESSION_KEY = 4;
static const uint8_t FRAME_IV = 5;
static const uint8_t NODEACTION_REQUEST = 2;
static const uint8_t NODEACTION_FILENAME = 3;
static const uint8_t FRAME_WATCHDDOG = 3;
static const uint8_t majver = 0;
static const uint8_t minver = 0;

/*constexpr
unsigned char secretKey[];*/

#endif
