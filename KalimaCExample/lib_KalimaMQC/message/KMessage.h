#ifndef KMESSAGE_H
#define KMESSAGE_H

#include <stdarg.h>
#include "Header.h"
#include "../crypto/aes.h"

typedef struct KMessage KMessage;
struct KMessage{
    struct Header *header;
	unsigned char** frames;
};

struct KMessage* KMessage_new();
struct KMessage* create_KMessage(unsigned char* frames, int nbFrames, int* sizes);
struct KMessage* create_KMessage2(int nbFrames, unsigned char* frame1, int size1, ...);
void construct_Header(struct KMessage*, int nbFrames, int* sizes);
struct Header* get_Header(struct KMessage*);
void set_Header(struct KMessage*, struct Header*);
unsigned char** get_Frames(struct KMessage*);
unsigned char* get_Frame(struct KMessage*, int i);
void set_Frames(struct KMessage*, unsigned char* frames, int nbFrames, int* sizes);
unsigned char *get_DEVID(struct KMessage*);
int get_Framesize(struct KMessage*, int i);
int get_DEVIDSize(struct KMessage*);
unsigned char* get_Frames_Bytes(struct KMessage*);
int get_Frames_Bytes_Size(struct KMessage*);
unsigned char* get_Bytes(struct KMessage*);
int get_Bytes_Size(struct KMessage*);
unsigned char* get_KMessage_Bytes(struct KMessage*);
int get_KMessage_Bytes_Size(struct KMessage*);
/*unsigned char* getEncryptedBytes();
static unsigned char* encrypt();
static KMessage decrypt();*/
struct KMessage build(unsigned char *data);
unsigned char encode_Type(int mestype);
unsigned char decode_Type(unsigned char bhead);
unsigned char get_Type(struct KMessage*);
void set_Type(struct KMessage* Kmessage, unsigned char type);
int get_Min_ver(int ver);
int get_Maj_ver(int ver);
int get_Ver(unsigned char bhead);
/*static bool sameVersion(unsigned char bhead);*/
int get_Min_ver_KM(struct KMessage*);
int get_Maj_ver_KM(struct KMessage*);
/*bool equals(KMessage o);*/

unsigned char* create_encrypted_message(unsigned char* msg_to_encrypt, int size);
void print_Header(struct Header *header);
void print_KMessage(struct KMessage *kMessage);

const unsigned char VOTEREQ;
const unsigned char VOTERESP;
const unsigned char VOTEAYT;
const unsigned char VOTEIHY;
const unsigned char VOTERES;
const unsigned char ADMIN;
const unsigned char AYT;
const unsigned char IHY;
const unsigned char PUB;
const unsigned char SUB;
const unsigned char SNAPSHOTREQ;
const unsigned char NODEACTION;
const unsigned char REQUEST_PUB;
const unsigned char SNAPSHOTRESP;
const unsigned char LEADER_PUB;

const int FRAME_DEVID;
const int FRAME_TYPE;
const int FRAME_CACHEPATH;
const int FRAME_SERIALID;
const int FRAME_SNASPHOT_TYPE;
const int NODEACTION_REQUEST;
const int NODEACTION_FILENAME;
const int majver;
const int minver;

/*constexpr
unsigned char secretKey[];*/

#endif
