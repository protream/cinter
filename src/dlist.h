#ifndef _DLIST_H_
#define _DLIST_H_

typedef struct list_node_s list_node_t;

struct list_node_s {
    void *val;
    list_node_t *next;
};

typedef struct {
    list_node_t *head;
    list_node_t *tail;
    void *(*dup)(void *ptr);
    void (*free)(void *ptr);
    void (*match)(void *ptr, void *key);
    unsigned long len;
} list_t;

#define list_length(l) ((l)->len)

/* API */
list_t *list_create(void);
void list_remove(list_t *l);
list_t *list_lpush(list_t *l, void *val);
list_t *list_rpush(list_t *l, void *val);
list_node_t *list_lpop(list_t *l);
list_node_t *list_rpop(list_t *l);
#endif /* _DLIST_H_ */
