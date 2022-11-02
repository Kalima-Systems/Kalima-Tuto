#ifndef HEADER_H
#define HEADER_H

/**
 * @file Header.h
 * @author André Legendre
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief KMessage's Header
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdint.h>

/**
 * @brief Header structure
 * 
 */
struct Header{
    int32_t headerSize; /**< Header's size */
	int32_t nbFrames; /**< Number of KMessage's frames */
	int32_t *sizes; /**< Array of frames' sizes */
};

/**
 * @brief Max number of frames in KMessage
 * 
 */
static const uint8_t MAX_FRAMES=41;

/**
 * @brief Create a Header
 * 
 * @param data KMessage's bytes
 * @return Pointer to Header 
 */
struct Header* create_Header(unsigned char *data);
/**
 * @brief Get Header as unsigned char array
 * 
 * @param header Pointer to Header
 * @return Header as array 
 */
unsigned char* header_to_array(struct Header* header);
/**
 * @brief Get Header's size
 * 
 * @param header Pointer to Header
 * @return Header's size
 */
int32_t get_Header_Size(struct Header* header);
/**
 * @brief Get the KMessages's number of frames from Header
 * 
 * @param header Pointer to Header
 * @return Number of frames
 */
int32_t get_Nb_Frames(struct Header* header);
/**
 * @brief Get the KMessage's frames sizes from Header
 * 
 * @param header Pointer to Header
 * @return Sizes array
 */
int32_t* get_Sizes(struct Header* header);
/**
 * @brief Set the Header size
 * 
 * @param header Pointer to Header
 * @param headerSize Header's size
 */
void set_Header_Size(struct Header* header, int32_t headerSize);
/**
 * @brief Set the number of KMessage's frames in Header
 * 
 * @param header Pointer to Header
 * @param nbFrames Number of frames
 */
void set_Nb_Frames(struct Header* header, int32_t nbFrames);
/**
 * @brief Set the KMessage's frames sizes in Header
 * 
 * @param header Pointer to Header
 * @param sizes Frames' sizes
 */
void set_Sizes(struct Header* header, int32_t *sizes);

/**
 * @brief Get Size as 4 entries array ([0]=w*256³, [1]=x*256², [2]=y*256, [3]=z)
 * 
 * @param entry_size Size to decompose
 * @param SizeArray Size array
 */
void decompose_size(int32_t entry_size, unsigned char* SizeArray);

/**
 * @brief Free a Header
 * 
 * @param header Pointer to Header
 */
void free_Header(struct Header* header);

#endif