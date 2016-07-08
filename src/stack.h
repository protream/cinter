/* stack.h */
#ifndef _STACK_H_
#define _STACK_H_

typedef struct stackNode {
    void *value;
    struct stackNode *next;
} stackNode;

typedef struct stack {
    stackNode *top;
    void (*free)(void *ptr);
    unsigned long size;
} stack;


/* Functions implemented as macros */
#define stackTop(s) ((s)->top)
#define stackSize(s) ((s)->size)
#define stackEmpty(s) ((s)->size == 0)

#define stackSetFreeMethod(s, m) ((s)->free = (m))
#define stackGetFreeMethod(s) ((s)->free)

stack *stackCreate(void);
stack *stackPush(stack *stack, void *value);
stackNode *stackPop(stack *stack);
void stackClear(stack *stack);
void stackFree(stack *stack);

#endif /* _STACK_H_ */
