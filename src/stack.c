#include <stdlib.h>
#include "stack.h"

stack *stackCreate(void)
{
    struct stack *s;

    if ((s = malloc(sizeof(*s))) == NULL)
        return NULL;
    s->top = NULL;
    s->free = NULL;
    s->size = 0;
    return s;
}

stack *stackPush(stack *s, void *value)
{
    stackNode *n;

    if ((n = malloc(sizeof(*n))) == NULL)
        return NULL;
    n->value = value;
    n->next = stackEmpty(s) ? NULL : s->top;
    s->top = n;
    s->size++;
    return s;
}

void *stackPop(stack *stack)
{
    stackNode *node;

    node = stack->top;
    if (!stackEmpty(stack)) {
        stack->top = node->next;
        stack->size--;
    }
    return node->value;
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

#ifdef STACK_TEST
#include "testhelper.h"

void stackTest(void)
{
    stack *s;
    stackNode *n;

    TEST("Create a stack: ") {
        s = stackCreate();
        assert(s != NULL);
        assert(s->free == NULL);
        assert(s->size == 0);
        ok();
    }

    TEST("Push item: ") {
        s = stackCreate();
        int v1 = 123;
        stackPush(s, &v1);
        assert(s->size == 1);
        assert(s->top->value == &v1);
        char *v2 = "foo";
        stackPush(s, v2);
        assert(s->size == 2);
        assert(s->top->value == v2);
        ok();
    }

    TEST("Pop item: ") {
        s = stackCreate();
        int v1 = 123;
        stackPush(s, &v1);
        char *v2 = "foo";
        stackPush(s, v2);
        n = stackPop(s);
        assert(n->value == v2);
        ok();
    }
}

#ifdef STACK_TEST_MAIN
int main(void) {
    stackTest();
}
#endif
#endif
