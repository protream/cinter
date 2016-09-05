//
// A skiplist implements on int value.
//
#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#define SKIPLIST_MAX_LEVEL 12
#define SKIPLIST_P 0.25

typedef struct skiplistNode {
    int value;
    struct skiplistLevel {
        struct skiplistNode *forward;
    } level[];
} skiplistNode;

typedef struct skiplistIter {
    skiplistNode *next;
} skiplistIter;

typedef struct skiplist {
    struct skiplistNode *header, *tail;
    unsigned int length;
    int level;
} skiplist;

#endif // SKIPLIST_H_
