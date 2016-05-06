/* dict.h -  A simpe hash table implementation */

#ifndef _DICT_H_
#define _DICT_H_

#define OK  0
#define ERR 1

typedef struct _dict_entry_t {
    const char *key;
    int   val;
    struct _dict_entry_t *next;
} dict_entry_t;

typedef struct _dict_t {
    unsigned int size;
    unsigned int count;
    dict_entry_t **entries;
} dict_t;

/* API */
dict_t *dict_create(unsigned int size);
dict_entry_t *dict_get(dict_t *d, const char *key);
dict_entry_t *dict_put(dict_t *d, const char *key, int val);
dict_entry_t *dict_del(dict_t *d, const char *key);
void dict_free(dict_t *d);

#endif /* ifndef _DICT_H_ */
