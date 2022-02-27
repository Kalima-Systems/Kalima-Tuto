#ifndef HEADER_H
#define HEADER_H

struct Header{
    int headerSize;
	int nbFrames;
	int *sizes;
};

const int MAX_FRAMES;

struct Header* create_Header(unsigned char *data);
unsigned char* header_to_array(struct Header*);
int get_Header_Size(struct Header*);
int get_Nb_Frames(struct Header*);
int* get_Sizes(struct Header*);
void set_Header_Size(struct Header*, int headerSize);
void set_Nb_Frames(struct Header*, int nbFrames);
void set_Sizes(struct Header*, int *sizes);
//SizeArray MUST be a Array_name[4]
void decompose_size(int entry_size, unsigned char* SizeArray);

#endif