/*-----------------------------------------------------------------------------
 * dict.c -  A simpe hash table implementation
 *
 * Copyright © 2016 protream(protream.gihub.io)
 *----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dict.h"

unsigned int _hash_str(const char *key, int size);


 /* 一个简单的字符串哈希函数 */
unsigned int _hash_str(const char *key, int size)
{
    unsigned int hv = 0;

    while (*key != '\0')
        hv += (hv << 5) + *key++;

    return hv % size;
}


/* 创建一个给定大小的字典(哈希表).
 *
 * 如果内存分配失败, 返回NULL, 否则返回指向新字典的指针. */
dict_t *dict_create(unsigned int size)
{
    dict_t *d;

    if ((d = (dict_t *)malloc(sizeof(dict_t))) == NULL)
        return NULL;
    if ((d->entries = (dict_entry_t **)malloc(size * sizeof(dict_entry_t *))) == NULL)
        return NULL;
    d->size = size;
    d->count = 0;

    return d;
}


/* 从字典中查找指定的key.
 *
 * 如果该key存在, 返回指向键值对实体的指针, 否则返回NULL. */
dict_entry_t *dict_get(dict_t *d, const char *key)
{
    dict_entry_t *e;
    unsigned int hv;

    hv = _hash_str(key, d->size);
    e  = d->entries[hv];
    while (e && strcmp(e->key, key) != 0)
        e = e->next;

    return e;
}

/* 添加键值对到字典.
 *
 * 如果字典中存在key, 返回NULL, 否则返回指向该键值对实体的指针 */
dict_entry_t *dict_put(dict_t *d, const char *key, int val)
{
    dict_entry_t *e;
    unsigned int hv;

    if ((e = dict_get(d, key)) != NULL)
        return NULL;
    if ((e = (dict_entry_t *)malloc(sizeof(dict_entry_t))) == NULL)
        return NULL;
    e->key = key;
    e->val = val;
    hv = _hash_str(key, d->size);
    e->next = d->entries[hv];
    d->entries[hv] = e;
    d->count++;

    return e;
}

/* 从字典中删除键值为key的实体.
 *
 * 如果key不存在返回NULL, 否则返回指向删除实体的指针. */
dict_entry_t *dict_del(dict_t *d, const char *key)
{
    dict_entry_t **curr, *e;
    unsigned int hv;

    hv = _hash_str(key, d->size);
    for (curr = d->entries + hv; *curr;) {
        e = *curr;
        if (e->key == key) {
            *curr = e->next;
            return e;
        } else {
            curr = &e->next;
        }
    }
    return NULL;
}

/* 释放字典 */
void dict_free(dict_t *d)
{
    unsigned int size;
    dict_entry_t *curr, *del;

    for (size = d->size; size; size--) {
        curr = *d->entries;
        while (curr) {
            del = curr;
            curr = curr->next;
            free(del);
        }
    }
    free(d);
}

/* test */
int main(int argc, char *argv[])
{
    return 0;
}
