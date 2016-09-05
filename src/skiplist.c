#include <stdlib.h>
#include "skiplist.h"

skiplistNode *skiplistCreateNode(int level, int value)
{
    skiplistNode *node;

    if ((node = malloc(sizeof(*node) + level*sizeof(struct skiplistLevel))) == NULL)
        return NULL;
    node->value = value;
    return node;
}

skiplist *skiplistCreate(void)
{
    int i;
    skiplist *sl;

    if ((sl = malloc(sizeof(*sl))) == NULL)
        return NULL;
    sl->level = 1;
    sl->length = 0;
    sl->header = skiplistCreateNode(SKIPLIST_MAX_LEVEL, 0);
    for (i = 0; i < SKIPLIST_MAX_LEVEL; i++)
        sl->header->level[i].forward = NULL;
    sl->tail = NULL;
    return sl;
}

void skiplistFree(skiplist *sl)
{
    skiplistNode *node = sl->header->level[0].forward, *next;

    free(sl->header);
    while (node) {
        next = node->level[0].forward;
        free(node);
        node = next;
    }
    free(sl);
}

int skiplistRandomLevel(void)
{
    int level = 1;

    while ((random()&0xFFFF) < (SKIPLIST_P*0xFFFF))
        level += 1;
    return (level < SKIPLIST_MAX_LEVEL) ? level : SKIPLIST_MAX_LEVEL;
}

skiplistNode *skiplistInsert(skiplist *sl, int value)
{
    int i, level;
    skiplistNode *update[SKIPLIST_MAX_LEVEL], *x;

    x = sl->header;
    for (i = sl->level-1; i >= 0; i--) {
        while (x->level[i].forward &&
               x->level[i].forward->value < value) {
            x = x->level[i].forward;
        }
        update[i] = x;
    }
    level = skiplistRandomLevel();
    if (level > sl->level) {
        for (i = sl->level; i < level; i--)
            update[i] = sl->header;
        sl->level = level;
    }
    x = skiplistCreateNode(level, value);
    for (i = 0; i < level; i++) {
        x->level[i].forward = update[i]->level[i].forward;
        update[i]->level[i].forward = x;
    }
    if (!x->level[0].forward)
        sl->tail = x;
    sl->length++;

    return x;
}

int skiplistDelete(skiplist *sl, int value)
{
    int i;
    skiplistNode *update[SKIPLIST_MAX_LEVEL], *x;

    x = sl->header;
    for (i = sl->level-1; i >=0; i--) {
        while (x->level[i].forward &&
               x->level[i].forward->value < value) {
            x = x->level[i].forward;
        }
        update[i] = x;
    }
    x = x->level[0].forward;
    if (x && value == x->value) {
        for (i = 0; i < sl->level; i++) {
            if (update[i]->level[i].forward == x)
                update[i]->level[i].forward = x->level[i].forward;
        }
        while (sl->level > 1 && sl->header->level[sl->level-1].forward == NULL)
            sl->level--;
        sl->length--;
        free(x);
        return 1;
    }
    return 0;
}


#ifdef SKIPLIST_TEST
#include "testhelper.h"

void skiplistTest(void)
{
    skiplist *sl;

    TEST("Cteate a skiplist: ") {
        sl = skiplistCreate();
        assert(sl != NULL);
        assert(sl->level == 1);
        assert(sl->header != NULL);
        assert(sl->tail == NULL);
        assert(sl->length == 0);
        ok();
    }

    TEST("Insert an item to skiplist: ") {
        sl = skiplistCreate();
        skiplistInsert(sl, 2);
        assert(sl->length == 1);
        assert(sl->header->level[0].forward != NULL);
        assert(sl->header->level[0].forward->value == 2);
        assert(sl->tail->value = 2);
        ok();
    }
}

#ifdef SKIPLIST_TEST_MAIN
int main(void)
{
    skiplistTest();
    return 0;
}
#endif
#endif
