// chaining-ht.h - A simple separate chaining hash table implementation.
#ifndef CHAINING_HT_H_
#define CHAINING_HT_H_

#define HT_MIN_INITIAL_SIZE 16

typedef struct htEntry {
    char *key;
    void *val;
    struct htEntry *next;
} htEntry;

typedef struct hashtb {
    void (*valDestructor)(void *obj);
    htEntry **table;
    unsigned long size;
    unsigned long used;
} hashtb;


hashtb *htCreate(unsigned int size);
int htSet(hashtb *ht, char *key, void *val);
void *htGet(hashtb *ht, char *key);
int htDel(hashtb *ht, char *key);

#endif // CHAINING_HT_H_
