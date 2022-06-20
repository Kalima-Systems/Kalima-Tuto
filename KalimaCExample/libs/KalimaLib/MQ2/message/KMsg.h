#ifndef KMSG_H
#define KMSG_H

#include "checksum.h"
#include "DevID.h"
#include "UUID.h"
#include "Header.h"
#include "KMessage.h"
#include "../../KalimaCUtil/logger.h"
#include "../../KalimaCUtil/BytesArray.h"
#include "../../KalimaCUtil/ByteBuffer.h"
#include "../nodelib/prop.h"

typedef struct KMsg KMsg;
struct KMsg{
    struct KMessage *Kmessage;
    char *key;
	int props_size;
    proplist Kprops;
};

// Message is formatted on wire as 14 frames the three first ones are reserved and defined in kMessage:
static const int KMSG_KEY_MAX = 800;
static const int FRAME_KEY = 3;
static const int FRAME_UUID = 4;
static const int FRAME_TERM = 5;
static const int FRAME_PTERM = 6; //previous TERM
static const int FRAME_SEQ = 7;
static const int FRAME_PREV = 8;
static const int FRAME_PROPS = 9;
static const int FRAME_BODY = 10;
static const int FRAME_SIGN = 11;
static const int FRAME_CHECK = 12;
static const int KMSG_FRAMES = 13;

KMsg* KMsg_new(int64_t sequence);
KMsg* setMessage(struct KMessage *message);
KMsg* getMessage(char* devID, int devID_size, char type, char* address, int address_size, char* key, int key_size, int64_t seq, char* body, int body_size, proplist kProps);

void decodeProps(KMsg *Kmsg);
KMsg* kmsg_dup(KMsg *Kmsg);
int64_t sign(KMsg *Kmsg);
int64_t sign_from_inputs(char* address, int address_size, char* key, int key_size, char* body, int body_size, char* props, int props_size);

unsigned char *getKey(KMsg *Kmsg);
void setKey(KMsg *Kmsg, char *key, int key_size);
void fmtKey(KMsg *Kmsg, char *format, int format_size, char* key, int key_size);

int64_t getTerm(KMsg *Kmsg);
void setTerm(KMsg *Kmsg, int64_t term);

unsigned char* getDevID(KMsg *Kmsg);
void setDevID(KMsg *Kmsg, char* devId, int devID_size);

int64_t getSequence(KMsg *Kmsg);
void setSequence(KMsg *Kmsg, int64_t sequence);

unsigned char* getBody(KMsg *Kmsg);
int getKeySize(KMsg *Kmsg);
void setBody(KMsg *Kmsg, char* body, int body_size);
void fmtBody(KMsg *Kmsg, char *format, int format_size, char* body, int body_size);

int msg_size(KMsg *Kmsg);

unsigned char* getUUID(KMsg *Kmsg);
void setUUID(KMsg *Kmsg);

unsigned char* getAddress(KMsg *Kmsg);
int getAddressSize(KMsg *Kmsg);
unsigned char* getSerialID(KMsg *Kmsg);
void setAddress(KMsg *Kmsg, char* address, int address_size);

void setProps(KMsg *Kmsg, char* kProps, int kProps_size);
void setPropsfromlist(KMsg *Kmsg, proplist kProps);
proplist getProps(KMsg *Kmsg);
unsigned char* getProp(KMsg *Kmsg, char* propName);
void setProp(KMsg *Kmsg, char* name, int name_size, char* value, int value_size);

unsigned char* getCheck(KMsg *Kmsg);
void setCheck(KMsg *Kmsg, char* check, int check_size);

unsigned char* getSign(KMsg *Kmsg);
void setSign(KMsg *Kmsg, char* sign, int sign_size);

int64_t getPrevious(KMsg *Kmsg);
void setPrevious(KMsg *Kmsg, int64_t prev);
int64_t getPrevTerm(KMsg *Kmsg);
void setPrevTerm(KMsg *Kmsg, int64_t term);
int getBodySize(KMsg *Kmsg);

void dump(KMsg *Kmsg);

void concat_for_check(char *final_array, char* devID, int devID_size, char type, 
                char *address, int address_size, char *key, int key_size, 
                char* uuid, int uuid_size, char* term, int term_size, char* pterm, int pterm_size, 
                char* seq, int seq_size, char* prev, int prev_size, char* props, int props_size, 
                char* body, int body_size, char* sign, int sign_size);

void concat_all(char *final_array, char* devID, int devID_size, char type, 
                char *address, int address_size, char *key, int key_size, 
                char* uuid, int uuid_size, char* term, int term_size, char* pterm, int pterm_size, 
                char* seq, int seq_size, char* prev, int prev_size, char* props, int props_size, 
                char* body, int body_size, char* sign, int sign_size, char* check, int check_size);

void concat_two(char *final_array, char* first, int first_size, char* second, int second_size);
int get_int_decimal_number(int integer);

#endif