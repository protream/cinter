// openht.h - An simple open address hash table.
#ifndef OPENHS_H_
#define OPENHS_H_

#define HT_MIN_INITIAL_SIZE 17

typedef struct htEntry {
    char *key;
    void *val;
} htEntry;

typedef struct hashtb {
    int size;
    int used;
    struct htEntry **table;
} hashtb;

hashtb *htCreate(int size);
int htSet(hashtb *ht, char *key, void *val);
htEntry *htGet(hashtb *ht, char *key);
htEntry *htDel(hashtb *ht, char *key);

#endif // OPENHS_H_
