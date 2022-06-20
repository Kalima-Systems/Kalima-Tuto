#ifndef HEADER_H
#define HEADER_H

#include <stdint.h>

struct Header{
    int32_t headerSize;
	int32_t nbFrames;
	int32_t *sizes;
};

static const uint8_t MAX_FRAMES=41;

struct Header* create_Header(unsigned char *data);
unsigned char* header_to_array(struct Header*);
int32_t get_Header_Size(struct Header*);
int32_t get_Nb_Frames(struct Header*);
int32_t* get_Sizes(struct Header*);
void set_Header_Size(struct Header*, int32_t headerSize);
void set_Nb_Frames(struct Header*, int32_t nbFrames);
void set_Sizes(struct Header*, int32_t *sizes);
//SizeArray MUST be a Array_name[4]
void decompose_size(int32_t entry_size, unsigned char* SizeArray);

#endif