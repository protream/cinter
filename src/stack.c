#define TEST_STACK

#include <stdlib.h>
#include "stack.h"


stack *stackCreate(void)
{
    struct stack *stack;

    if ((stack = (struct stack *)malloc(sizeof(struct stack))) == NULL)
        return NULL;
    stack->top = NULL;
    stack->free = NULL;
    stack->size = 0;
    return stack;
}

stack *stackPush(stack *stack, void *value)
{
    stackNode *node;

    if ((node = (stackNode *)malloc(sizeof(stackNode))) == NULL)
        return NULL;
    node->value = value;
    node->next = stackEmpty(stack) ? NULL : stack->top;
    stack->top = node;
    stack->size++;
    return stack;
}

stackNode *stackPop(stack *stack)
{
    stackNode *node;

    node = stack->top;
    if (!stackEmpty(stack)) {
        stack->top = node->next;
        stack->size--;
    }
    return node;
}

void stackClear(stack *stack)
{
    unsigned long size;
    stackNode *current, *next;

    current = stack->top;
    size = stack->size;
    while (size--) {
        next = current->next;
        if (stack->free) stack->free(current->value);
        free(current);
        current = next;
    }
    stack->size = 0;
    stack->top = NULL;
}


void stackFree(stack *stack)
{
    if (!stackEmpty(stack)) stackClear(stack);
    free(stack);
}

#ifdef TEST_STACK
#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    stack *stack;
    stackNode *node;

    stack = stackCreate();
    assert(stack != NULL);
    assert(stack->free == NULL);
    assert(stack->size == 0);

    int v1 = 123;

    stackPush(stack, &v1);
    assert(stack->size == 1);
    assert(stack->top->value == &v1);

    char *v2 = "foo";

    stackPush(stack, v2);
    assert(stack->size == 2);
    assert(stack->top->value == v2);

    node = stackPop(stack);
    assert(node->value == v2);
    assert(stack->size == 1);

    stackClear(stack);
    assert(stack->size == 0);
    assert(stack->top == NULL);

    printf("Test stack OK!\n");

    return 0;
}
#endif
