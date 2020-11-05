#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
namespace cst {
#endif

#ifndef CST_STACK_TYPE
#define CST_STACK_TYPE int
#endif

struct CstStackNode
{
	CST_STACK_TYPE value;
	struct CstStackNode *next;
};

struct CstStackNode *csn_create(CST_STACK_TYPE value, struct CstStackNode *next)
{
	struct CstStackNode *rslt = (struct CstStackNode*)malloc(sizeof(struct CstStackNode));
	rslt->value = value;
	rslt->next = next;
	return rslt;
}

typedef struct Stack
{
	size_t size;
	struct CstStackNode *top;
} Stack;

Stack stack_create()
{
	Stack rslt = {0, NULL};
	return rslt;
}

Stack stack_copy(Stack *src)
{
	Stack rslt = {src->size, NULL};
	struct CstStackNode *n = src->top;
	while (n)
	{
		rslt.top = csn_create(n->value, rslt.top);
		n = n->next;
	}
	return rslt;
}

void stack_push(Stack *stack, CST_STACK_TYPE value)
{
	stack->top = csn_create(value, stack->top);
	stack->size++;
}

int stack_pop(Stack *stack)
{
	if (stack->size == 0) return -1;
	stack->top = stack->top->next;
	return 0;
}

void stack_destroy(Stack *stack)
{
	while (stack->top)
	{
		struct CstStackNode *temp = stack->top;
		stack->top = stack->top->next;
		free(temp);
	}
}

#ifdef __cplusplus
}
#endif

/*
using namespace cst;

void putstack(Stack *stack)
{
	struct CstStackNode *n = stack->top;
	while (n)
	{
		printf("%d", n->value);
		if ((n = n->next)) printf("->");
	}
	putchar(0xa);
}

int main()
{
	Stack s = stack_create();
	stack_push(&s, 10);
	putstack(&s);
	stack_push(&s, 9);
	putstack(&s);
	stack_push(&s, 8);
	putstack(&s);
	stack_pop(&s);
	putstack(&s);
	stack_pop(&s);
	putstack(&s);
	stack_pop(&s);
	putstack(&s);


	return 0;
}
*/
