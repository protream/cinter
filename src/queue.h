#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct queueNode {
    void *val;
    struct queueNode *next;
} queueNode;

typedef struct queue {
    queueNode *head;
    queueNode *tail;
    unsigned int len;
} queue;


queue *queueCreate(void);
queue *queuePush(queue *q, void *val);
void *queueFront(queue *q);
queueNode *queuePop(queue *q);

#endif // QUEUE_H_
