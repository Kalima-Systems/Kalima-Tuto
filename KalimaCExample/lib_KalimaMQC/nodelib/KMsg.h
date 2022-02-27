#ifndef KMSG_H
#define KMSG_H

#include "../message/checksum.h"
#include "../message/DevID.h"
#include "../message/UUID.h"
#include "../message/Header.h"
#include "../message/KMessage.h"
#include "logger.h"
#include "prop.h"
#include "ByteBuffer.h"

typedef struct KMsg KMsg;
struct KMsg{
    struct KMessage *Kmessage;
    char *key;
	int props_size;
    proplist Kprops;
};

const int KMSG_KEY_MAX;

// Message is formatted on wire as 14 frames the three first ones are reserved and defined in kMessage:
const int FRAME_KEY;
const int FRAME_UUID;
const int FRAME_TERM;
const int FRAME_PTERM; //previous TERM
const int FRAME_SEQ;
const int FRAME_PREV;
const int FRAME_PROPS;
const int FRAME_BODY;
const int FRAME_SIGN;
const int FRAME_CHECK;
const int KMSG_FRAMES;

KMsg* KMsg_new(int64_t sequence);
KMsg* setMessage(struct KMessage *message);
KMsg* getMessage(char* devID, int devID_size, char type, char* cachePath, int cachePath_size, char* key, int key_size, int64_t seq, char* body, int body_size, proplist kProps);

void decodeProps(KMsg *Kmsg);
KMsg* kmsg_dup(KMsg *Kmsg);
int64_t sign(KMsg *Kmsg);
int64_t sign_from_inputs(char* cachePath, int cachePath_size, char* key, int key_size, char* body, int body_size, char* props, int props_size);

unsigned char *getKey(KMsg *Kmsg);
void setKey(KMsg *Kmsg, char *key, int key_size);
void fmtKey(KMsg *Kmsg, char *format, char* key, int key_size);

int64_t getTerm(KMsg *Kmsg);
void setTerm(KMsg *Kmsg, int64_t term);

unsigned char* getDevID(KMsg *Kmsg);
void setDevID(KMsg *Kmsg, char* devId, int devID_size);

int64_t getSequence(KMsg *Kmsg);
void setSequence(KMsg *Kmsg, int64_t sequence);

unsigned char* getBody(KMsg *Kmsg);
void setBody(KMsg *Kmsg, char* body, int body_size);
void fmtBody(KMsg *Kmsg, char *format, char* body, int body_size);

int msg_size(KMsg *Kmsg);

unsigned char* getUUID(KMsg *Kmsg);
void setUUID(KMsg *Kmsg);

unsigned char* getCachePath(KMsg *Kmsg);
unsigned char* getSerialID(KMsg *Kmsg);
void setCachePath(KMsg *Kmsg, char* cachePath, int cachePath_size);

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
                char *cachePath, int cachePath_size, char *key, int key_size, 
                char* uuid, int uuid_size, char* term, int term_size, char* pterm, int pterm_size, 
                char* seq, int seq_size, char* prev, int prev_size, char* props, int props_size, 
                char* body, int body_size, char* sign, int sign_size);

void concat_all(char *final_array, char* devID, int devID_size, char type, 
                char *cachePath, int cachePath_size, char *key, int key_size, 
                char* uuid, int uuid_size, char* term, int term_size, char* pterm, int pterm_size, 
                char* seq, int seq_size, char* prev, int prev_size, char* props, int props_size, 
                char* body, int body_size, char* sign, int sign_size, char* check, int check_size);

void concat_two(char *final_array, char* first, int first_size, char* second, int second_size);
int get_int_decimal_number(int integer);

#endif