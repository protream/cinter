#include <stdlib.h>
#include "queue.h"

// create a queue.
queue *queueCreate(void)
{
    queue *q;

    if ((q = malloc(sizeof(*q))) == NULL)
        return NULL;
    q->len = 0;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

queue *queuePush(queue *q, void *val)
{
    queueNode *n;

    if ((n = malloc(sizeof(*n))) == NULL)
        return q;
    n->val = val;
    n->next = NULL;
    if (q->len == 0)
        q->head = q->tail = n;
    else {
        q->tail->next = n;
        q->tail = n;
    }
    q->len++;
    return q;
}

void *queueFront(queue *q)
{
    if (q->len)
        return q->head->val;
    return NULL;
}

queueNode *queuePop(queue *q)
{
    queueNode *n;

    if (q->len == 0)
        return NULL;
    n = q->head;
    q->head = n->next;
    q->len--;
    return n;
}

#ifdef QUEUE_TEST
#include "testhelper.h"

void queueTest(void)
{
    queue *q;

    TEST("Create a queue: ") {
        q = queueCreate();
        assert(q != NULL);
        assert(q->head == NULL);
        assert(q->tail == NULL);
        assert(q->len == 0);
        ok();
    }

    TEST("Push an item: ") {
        q = queueCreate();
        assert(q != NULL);
        int a = 1;
        queuePush(q, &a);
        assert(q->head->val == &a);
        assert(q->tail->val == &a);
        assert(q->len == 1);
        assert(queueFront(q) == &a);
        ok();
    }

    TEST("Pop an item: ") {
        q = queueCreate();
        assert(q != NULL);
        char *s = "hello, queue!";
        queueNode *n = NULL;
        queuePush(q, s);
        n = queuePop(q);
        assert(n);
        assert(n->val == s);
        assert(q->len == 0);
        ok();
    }
}

int main(void)
{
    queueTest();
    return 0;
}
#endif
