#ifndef COMPARE_H
#define COMPARE_H

#include "skiplist.h"

int CmpKey( SkipListNode_t *node, SkipListNode_t *obj );
int CmpInt( SkipListNode_t *node, SkipListNode_t *obj );
int CmpOrder( SkipListNode_t *node, SkipListNode_t *obj );
void myFree();

#endif