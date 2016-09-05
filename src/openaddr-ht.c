#include <stdlib.h>
#include <string.h>
#include "openaddr-ht.h"

static unsigned int hashFunc(char *buf, int len)
{
    unsigned int hash = 5381;

    while (len--) {
        hash += ((hash << 5) + hash) + (*buf++);
    }
    return hash;
}

// Create a new hashtable.
hashtb *htCreate(int size)
{
    int i;
    hashtb *ht;

    if ((ht = malloc(sizeof(*ht))) == NULL)
        return NULL;
    if (size < HT_MIN_INITIAL_SIZE) size = HT_MIN_INITIAL_SIZE;
    if ((ht->table = malloc(size * sizeof(htEntry*))) == NULL)
        return NULL;
    for (i = 0; i < size; ++i) {
        ht->table[i] = NULL;
    }
    ht->size = size;
    ht->used = 0;
    return ht;
}

// Add key:val to hashtable.
//
// returns:
//     -1: out of memory.
//      0: success.
//      1: key already exists, its val be overwrited by the new val.
int htSet(hashtb *ht, char *key, void *val)
{
    int index, i = 0;
    htEntry *e;

    index = hashFunc(key, strlen(key)) % ht->size;
    while (ht->table[index] != NULL) {
        if (!strcmp(ht->table[index]->key, key)) {
            ht->table[index]->val = val;
            return 1;
        }
        index = 2 * ++i - 1;
        if (index >= ht->size) index -= ht->size;
    }
    if ((e = malloc(sizeof(*e))) == NULL)
        return -1;
    e->key = key;
    e->val = val;
    ht->table[index] = e;
    ht->used++;
    return 0;
}

htEntry *htGet(hashtb *ht, char *key)
{
    int index, i = 0;

    index = hashFunc(key, strlen(key)) % ht->size;
    while (ht->table[index] != NULL) {
        if (!strcmp(ht->table[index]->key, key)) {
            return ht->table[index];
        }
        index = 2 * ++i - 1;
        if (index >= ht->size) index -= ht->size;
    }
    return NULL;
}

htEntry *htDel(hashtb *ht, char *key)
{
    return NULL;
}

#ifdef OPENADDRHT_TEST
#include "testhelper.h"

void openaddrhtTest()
{
    hashtb *ht;
    void *val;

    ht = htCreate(6);
    assert(ht != NULL);
    assert(ht->size == 31);
    assert(ht->used == 0);
    assert(ht->table != NULL);


    assert(htSet(ht, "1", "one") == 0);
    assert(ht->used == 1);
    val = htGet(ht, "1")->val;
    assert(strcmp((char*)val, "one") == 0);

    assert(htSet(ht, "2", "two") == 0);
    assert(ht->used == 2);

    assert(htSet(ht, "3", "thee") == 0);
    val = htGet(ht, "3")->val;
    assert(strcmp((char*)val, "thee") == 0);
    assert(ht->used == 3);
    assert(htSet(ht, "3", "three") == 1);
    assert(ht->used == 3);
    val = htGet(ht, "3")->val;
    assert(strcmp((char*)val, "three") == 0);

    assert(htGet(ht, "4") == NULL);
}

#ifdef OPENADDRHT_TEST_MAIN
int main(void)
{
    openaddrhtTest();
    return 0;
}
#endif
#endif
