#ifndef SKIPLIST_H
#define SKIPLIST_H
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif
    
/***************************************************************************
 *                             M A C R O S
 ***************************************************************************/

#define SKIPLIST_MAXLEVEL        16

#define SKIPLIST_NUM_NODES(l)    (l->numNodes)
#define SKIPLIST_NODE_FIRST(l)   (l->header->forward[0])
#define SKIPLIST_NODE_NEXT(n)    (n->forward[0])
#define SKIPLIST_NODE_VALUE(n)   (n ? n->value : NULL)

/***************************************************************************
 *                            T Y P E  D E F I N I T I O N S
 ***************************************************************************/

typedef void (*SkipListFree_t) (void *value);

typedef void * (*SkipListUserAlloc_t)(void *key, void *data, void **newKey, void **newData);

typedef struct SkipListNode_s {
    void           *key;
    int             key_size;
    void           *value;
    int             value_size;
    int             order;
	unsigned char	level;
	unsigned char	reserved[3];
    struct SkipListNode_s *forward[1]; /* var size array of forward pointers */
} SkipListNode_t;

typedef int  (*SkipListCmp_t)  (SkipListNode_t *node, SkipListNode_t *obj);

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

/***************************************************************************
 * Function    : SkipListAlloc()
 * Description : Allocates a new skip list. 
 * Input       : Pointer to the compare function which is used to compare 
 *               the keys and a pointer to the free function which is used
 *               to free the element stored in each skip list node. 
 * Output      : None.
 * Returns     : Pointer to the newly allocated skip list.
 * ***************************************************************************/
SkipList_t *SkipListAlloc( SkipListCmp_t cmpFn, SkipListFree_t freeFn );

/***************************************************************************
 * Function    : SkipListFree()
 * Description : Frees the given skip list. 
 * Input       : Pointer to the skip list to be freed.
 * Output      : None.
 * Returns     : None. 
 ****************************************************************************/
void SkipListFree( SkipList_t *list );

/***************************************************************************
 * Function    : SkipListInstert()
 * Description : Inserts the given element in the skip list at
 *               the right place based on the specified key. 
 * Input       : The list in which the element is to be inserted, key,
 *               element to be inserted and a flag which indicates
 *               whether to replace the existing element, if any. 
 * Output      : None.
 * Returns     : 0 -- success, -1 -- failure
 * ***************************************************************************/
int SkipListInsert( SkipList_t *list, SkipListNode_t *obj, int replace );

/***************************************************************************
 * Function    : SkipListDelete()
 * Description : Deletes the matching element from the list. 
 * Input       : Pointer to the list and the key whose corresponding
 *               entry is to be deleted from the list (+key_size). 
 * Output      : None.
 * Returns     : 0 -- success, -1 -- failure
 ****************************************************************************/
int SkipListDelete( SkipList_t *list, void *key, int key_size, int type); 

/***************************************************************************
 * Function    : SkipListGetNode()
 * Description : Finds the matching node for the given key. 
 * Input       : Pointer to the list and the key whose matching
 *               element is to be found. 
 * Output      : None.
 * Returns     : Pointer to the matching node.
 ****************************************************************************/
SkipListNode_t *SkipListGetNode( SkipList_t *list, void *key, int key_size );

/***************************************************************************
 * Function    : SkipListGetNodeOrNext()
 * Description : Gets the node or if not present, the next node
 *               in the list based on the key. 
 * Input       : Pointer to the list and the key . 
 * Output      : None.
 * Returns     : Pointer to the node or if not found, the next node.
 * ***************************************************************************/
SkipListNode_t *SkipListGetNodeOrNext( SkipList_t *list, void *key, int key_size );

/***************************************************************************
 * Function    : SkipListGetCount()
 * Description : Gets the total number of elements in the list.
 * Input       : Pointer to the list.
 * Output      : None.
 * Returns     : Number of elements in the skip list.
 ****************************************************************************/
int SkipListGetCount( SkipList_t *list );

/***************************************************************************
 * Function    : SkipListGetFirst()
 * Description : Gets the first node in the list.
 * Input       : Pointer to the list.
 * Output      : None.
 * Returns     : Pointer to the first node in the list.
 ****************************************************************************/
SkipListNode_t *SkipListGetFirst( SkipList_t *list );

/***************************************************************************
 * Function    : SkipListGetPrevious()
 * Description : Gets the previous node in the list based on the key.
 * Input       : Pointer to the list and the key whose lexicographically
 *               previous node is to be found. 
 * Output      : None.
 * Returns     : Pointer to the previous node in the list.
 * ***************************************************************************/
SkipListNode_t *SkipListGetPrevious( SkipList_t *list, void *key, int key_size );

/***************************************************************************
 * Function    : SkipListGetNext()
 * Description : Gets the next node in the list based on the key.
 * Input       : Pointer to the list and the key whose lexicographically
 *               next node is to be found. 
 * Output      : None.
 * Returns     : Pointer to the next node in the list.
 ****************************************************************************/
SkipListNode_t *SkipListGetNext( SkipList_t *list, void *key, int key_size );


/***************************************************************************
 * Function    : SkipListFindOrInsert()
 * Description : Searches for the specified data item
 *               If found returns it, otherwise allocates one using
 *               user specified function, sets key and data and then
 *               returns it. 
 *               If no user specified function exists, the given key
 *               and data are inserted.
 *              
 *
 * Input       : The list in which the element is to be inserted, key,
 *               element to be inserted, a allocation function if new key and
 *               data are to be allocated, a return value for a flag to indicate
 *               if allocation was called.
 * Output      : sets found if it found an element.
 * Returns     : Node ptr on success, NULL on failiure
 * ***************************************************************************/
SkipListNode_t *
SkipListFindOrInsert( SkipList_t *list, void *key, int key_size, void *value , int value_size, SkipListUserAlloc_t allocFn, int *found );

/***************************************************************************
 * Function    : SkipListClear()
 * Description : Frees all data items on the skiplist.
 * Input       : Pointer to the skip list to be cleared.
 * Output      : None.
 * Returns     : None. 
 ****************************************************************************/
void
SkipListClear( SkipList_t *list );

/***************************************************************************
 * Function    : SkipListDeleteNode()
 * Description : Deletes the matching node from the list. 
 * Input       : Pointer to the list and the key whose corresponding
 *               NODE is to be deleted from the list. 
 *               The FREE FUNCTION is NOT called.
 *               This is useful in cases where the structure needs to be preserved
 *               without having to provide a dummy free function
 * Output      : None.
 * Returns     : 0 -- success, -1 -- failure
 ****************************************************************************/
int
SkipListDeleteNode( SkipList_t *list, void *key, int key_size );



/***************************************************************************
 * Function    : SkipListNClear()
 * Description : Frees n data items on the skiplist.
 * Input       : Pointer to the skip list to be cleared.
 * Output      : None.
 * Returns     : None. 
 ****************************************************************************/
void SkipListNClear( SkipList_t *list , int n) ;

/***************************************************************************
 * Function    : get_Nb_in_interval()
 * Description : Gets the number of nodes in the interval.
 * Input       : Pointer to the list and the keys who form the interval. 
 * Output      : None.
 * Returns     : Number of nodes in the interval (int value).
 * ***************************************************************************/
int get_Nb_in_interval(SkipList_t *list, void *key1, int key_size1, void *key2, int key_size2);

/***************************************************************************
 * Function    : SkipListGetInterval()
 * Description : Gets the nodes in the list between the keys.
 * Input       : Pointer to the list and the keys who form the interval. 
 * Output      : None.
 * Returns     : Pointer to the nodes in the interval.
 * ***************************************************************************/
SkipListNode_t **SkipListGetInterval(SkipList_t *list, void *key1, int key_size1, void *key2, int key_size2);

/***************************************************************************
 * Function    : SkipListSort()
 * Description : Sort the list with a compare function.
 * Input       : Pointer to the list, compare function and free function. 
 * Output      : None.
 * Returns     : None.
 * ***************************************************************************/
void SkipListSort( SkipList_t * list, SkipListCmp_t cmpFn, SkipListFree_t freeFn );

/***************************************************************************
 * Function    : createObject()
 * Description : Create an object.
 * Input       : key, key size, value, value size and number of nodes already 
 *               in the listt. 
 * Output      : None.
 * Returns     : Pointer to the nodes in the interval.
 * ***************************************************************************/
SkipListNode_t *createObject(void *key, int key_size, void *value, int value_size, int numNodes);

#ifdef __cplusplus
}
#endif

#endif /* SKIPLIST_H */

