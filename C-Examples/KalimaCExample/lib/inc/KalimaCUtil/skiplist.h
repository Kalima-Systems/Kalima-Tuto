#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file skiplist.h
 * @author Louis Germanicus (louis.germanicus@kalima.io)
 * @brief SkipList code to handle key/value store
 * @details Based on code from http://www2.ee.unsw.edu.au/~vijay/research/smallbuffersCode/skiplist/
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
    
/***************************************************************************
 *                             M A C R O S
 ***************************************************************************/

#define SKIPLIST_MAXLEVEL        16

#define SKIPLIST_NUM_NODES(l)    (l->numNodes)
#define SKIPLIST_NODE_FIRST(l)   (l->header->forward[0])
#define SKIPLIST_NODE_NEXT(n)    (n->forward[0])

/***************************************************************************
 *                            T Y P E  D E F I N I T I O N S
 ***************************************************************************/


typedef void (*SkipListFree_t) (void *key);

typedef void * (*SkipListUserAlloc_t)(void *key, void **newKey);

typedef struct SkipListNode_s {
    void           *key;
    int            position;
	unsigned char	level;
	unsigned char	reserved[3];
    struct SkipListNode_s *forward[1]; /* var size array of forward pointers */
} SkipListNode_t;

typedef int  (*SkipListCmp_t)  (SkipListNode_t *obj1, SkipListNode_t *obj2);

typedef struct SkipList_s {
    int             numNodes; 
    int             maxLevels; 
    int             level;         /* Maximum level of the list (1 more than
                                   the number of levels in the list) */
    SkipListCmp_t   cmpFn;
    SkipListFree_t  freeFn;

    void            **bh;

    SkipListNode_t  *header;    /* pointer to header */
}
SkipList_t;

/***************************************************************************
 *                    F U N C T I O N   P R O T O T Y P E S
 ***************************************************************************/

/**
 * @brief Initialize a new node
 * 
 * @param key Node data
 * @param position Position in SkipList
 * @return Pointer to SkipListNode_t
 */
SkipListNode_t *newNode(void *key, int position);

/**
 * @brief Allocates a new skip list
 * 
 * @param cmp Pointer to the compare function which is used to compare the keys
 * @param free Pointer to the free function which is used to free the element stored in each skip list node
 * @return Pointer to the newly allocated skip list 
 */
SkipList_t *SkipListAlloc( SkipListCmp_t cmp, SkipListFree_t free);

/**
 * @brief Frees the given skip list
 * @param skiplist Pointer to the skip list to be freed
 * 
 */
void SkipListFree( SkipList_t * skiplist);

/**
 * @brief Inserts the given element in the skip list at the right place based on the specified key
 * 
 * @param skiplist List in which the element is to be inserted
 * @param key Key : element to be inserted
 * @param replace Flag which indicates whether to replace the existing element, if any (1 : replace)
 * @return 0 -- success, -1 -- failure
 */
int SkipListInsert( SkipList_t *skiplist, void *key, int replace);

/**
 * @brief Deletes the matching element from the list
 * 
 * @param skiplist Pointer to the list
 * @param key Key whose corresponding entry is to be deleted from the list
 * @return 0 -- success, -1 -- failure
 */
int SkipListDelete( SkipList_t *skiplist, void *key); 

/**
 * @brief Finds the matching node for the given key
 * 
 * @param skiplist Pointer to the list
 * @param key Key whose matching element is to be found
 * @return Pointer to the matching node 
 */
SkipListNode_t *SkipListGetNode( SkipList_t *skiplist, void *key );

/**
 * @brief Gets the node or if not present, the next node in the list based on the key
 * 
 * @param skiplist Pointer to the list
 * @param key Key whose matching element is to be found
 * @return Pointer to the node or if not found, the next node 
 */
SkipListNode_t *SkipListGetNodeOrNext( SkipList_t *skiplist, void *key );

/**
 * @brief Gets the total number of elements in the list
 * 
 * @param skiplist Pointer to the list
 * @return Number of elements in the skip list
 */
int SkipListGetCount( SkipList_t *skiplist );

/**
 * @brief Gets the first node in the list
 * 
 * @param skiplist Pointer to the list
 * @return Pointer to the first node in the list 
 */
SkipListNode_t *SkipListGetFirst( SkipList_t *skiplist );

/**
 * @brief Gets the previous node in the list based on the key
 * 
 * @param skipllist Pointer to the list
 * @param key Key whose lexicographically previous node is to be found
 * @return Pointer to the previous node in the list 
 */
SkipListNode_t *SkipListGetPrevious( SkipList_t *skipllist, void *key);

/**
 * @brief Gets the next node in the list based on the key
 * 
 * @param skiplist Pointer to the list
 * @param key Key whose lexicographically next node is to be found
 * @return Pointer to the next node in the list 
 */
SkipListNode_t *SkipListGetNext( SkipList_t *skiplist, void *key );

/**
 * @brief Searches for the specified data item
 * @details If found returns it, otherwise allocates one using user specified function, sets key and data and then returns it\n
 *          If no user specified function exists, the given key and data are inserted
 * 
 * @param skiplist List in which the element is to be inserted
 * @param key Key, element to be inserted
 * @param found return value for a flag to indicate if allocation was called
 * @return Node pointer on success, NULL on failiure 
 */
SkipListNode_t *SkipListFindOrInsert( SkipList_t *skiplist, void *key, int *found );

/**
 * @brief Frees all data items on the skiplist
 * 
 * @param skiplist Pointer to the skip list to be cleared
 */
void SkipListClear( SkipList_t *skiplist );

/**
 * @brief Deletes the matching node from the list
 * @details The FREE FUNCTION is NOT called\n 
 *          This is useful in cases where the structure needs to be preserved without having to provide a dummy free function
 * 
 * @param skiplist Pointer to the list
 * @param key Key whose corresponding NODE is to be deleted from the list
 * @return 0 -- success, -1 -- failure
 */
int SkipListDeleteNode( SkipList_t *skiplist, void *key);

/**
 * @brief Frees n data items on the skiplist
 * 
 * @param skiplist Pointer to the skip list to be cleared
 * @param n Number of data to free
 */
void SkipListNClear( SkipList_t *skiplist , int n) ;

/**
 * @brief Gets the number of nodes in the interval
 * 
 * @param skiplist Pointer to the list
 * @param key1 Key 1 of interval
 * @param key2 Key 2 of interval
 * @return Number of nodes in the interval (int value)
 */
int get_Nb_in_interval(SkipList_t *skiplist, void *key1, void *key2);

/**
 * @brief Gets the nodes in the list between the keys
 * 
 * @param skiplist Pointer to the list
 * @param key1 Key 1 of interval
 * @param key2 Key 2 of interval
 * @return Pointer to the nodes in the interval 
 */
SkipListNode_t **SkipListGetInterval(SkipList_t *skiplist, void *key1, void *key2);

/**
 * @brief Sort the list with a compare function
 * 
 * @param skiplist Pointer to the list
 * @param cmpFn Compare function
 * @param freeFn Free function
 */
void SkipListSort( SkipList_t * skiplist, SkipListCmp_t cmpFn, SkipListFree_t freeFn );

/**
 * @brief Update positions of the skiplist
 * 
 * @param skiplist Pointer to the list
 */
void SkiplistUpdatePosition(SkipList_t * skiplist);

#endif /* SKIPLIST_H */