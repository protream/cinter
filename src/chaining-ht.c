#include <stdlib.h>
#include <string.h>
#include "chaining-ht.h"

static unsigned int hashFunc(const char *buf, int len)
{
    unsigned int hash = 5381;

    while (len--)
        hash = ((hash << 5) + hash) + (*buf++); // hash * 33 + c
    return hash;
}

// Create a hash table with give size. The min size is 16.
// If give size < 16, if will be set to 16.
//
// return:
//     -1: Out of memery.
//     ht: A point to the hash table.
hashtb *htCreate(unsigned int size)
{
    hashtb *ht;
    unsigned int i;

    if (size < HT_MIN_INITIAL_SIZE)
        size = HT_MIN_INITIAL_SIZE;
    if ((ht = malloc(sizeof(ht))) == NULL)
        return NULL;
    if ((ht->table = (size * sizeof(htEntry*))) == NULL)
        return NULL;
    for (i = 0; i < size; ++i)
        ht->table[i] = NULL;
    ht->valDestructor = NULL;
    ht->size = size;
    ht->used = 0;
    return ht;
}

// Add key:val to hashtable.
//
// returns:
//     -1: Out of memery.
//      0: Add success.
//      1: Key already exist.
int htSet(hashtb *ht, char *key, void *val)
{
    int index;
    htEntry *e, *curr;

    if ((e = malloc(sizeof(htEntry))) == NULL) {
        return -1;
    }
    index = hashFunc(key, strlen(key)) % ht->size;
    curr = ht->table[index];
    while (curr) {
        if (!strcmp(curr->key, key)) {
            return 1;
        }
        curr = curr->next;
    }
    e->key = key;
    e->val = val;
    e->next = ht->table[index];
    ht->table[index] = e;
    ht->used++;
    return 0;
}

// Get val from ht according to the key.
//
// return:
//      val: If key exists, return a void pointer to the val.
//     NULL: Key not exists.
void *htGet(hashtb *ht, char *key)
{
    int index;
    htEntry *curr;

    index = hashFunc(key, strlen(key)) % ht->size;
    curr = ht->table[index];
    while (curr) {
        if (!strcmp(curr->key, key))
            return curr->val;
        curr = curr->next;
    }
    return NULL;
}

// Delete the key:val according to the key.
//
// return:
//     0: del success.
//    -1: key not exists.
int htDel(hashtb *ht, char *key)
{
    unsigned long i;
    htEntry *prev, *curr;

    for (i = 0; i < ht->size; ++i) {
        prev = NULL;
        curr = ht->table[i];
        while (curr) {
            if (!strcmp(curr->key, key)) {
                if (prev == NULL) {
                    ht->table[i] = curr->next;
                } else {
                    prev->next = curr->next;
                }
                free(curr);
                ht->used--;
                return 0;
            }
            prev = curr;
            curr = curr->next;
        }
    }
    return -1;
}

#ifdef CHAININGHT_TEST
#include "testhelper.h"

void charninghtTest(void)
{
    hashtb *ht;
    void *val;

    ht = htCreate(16);
    assert(ht->size == 16);
    assert(ht->used == 0);

    assert(htSet(ht, "apple", "1234") == 0);
    val = htGet(ht, "apple");
    assert(strcmp((char*)val, "1234") == 0);

    assert(htSet(ht, "apple", "1235") == 1);

    assert(htSet(ht, "google", "5678") == 0);
    val = htGet(ht, "google");
    assert(val);
    assert(strcmp((char*)val, "5678") == 0);

    assert(ht->used == 2);

    assert(htDel(ht, "google") == 0);
    assert(htGet(ht, "google") == NULL);
    assert(htDel(ht, "facebook") == -1);

    assert(ht->used == 1);
}

#ifdef CHAININGHT_TEST_MAIN
int main(int argc, char *argv[])
{
    charninghtTest();
    return 0;
}
#endif
#endif
