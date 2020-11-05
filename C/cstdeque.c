#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1<->2<->3<->5
// Back = 1
// Front = 5

#ifndef CST_DEQUE_TYPE
#define CST_DEQUE_TYPE int
#endif

#ifdef __cplusplus
namespace cst {
#endif

struct CstDequeNode
{
	CST_DEQUE_TYPE value;
	struct CstDequeNode *next;
	struct CstDequeNode *prev;
};

struct CstDequeNode *cqn_create(CST_DEQUE_TYPE value, struct CstDequeNode *next, struct CstDequeNode *prev)
,{
	struct CstDequeNode *rslt =(struct CstDequeNode*) malloc(sizeof(struct CstDequeNode));
	rslt->value = value;
	rslt->next = next;
	rslt->prev = prev;
	return rslt;
}

typedef struct Deque
{
	size_t size;
	struct CstDequeNode *back;
	struct CstDequeNode *front;
} Deque;

Deque deque_create()
{
	Deque rslt = {0, NULL, NULL};
	return rslt;
}

void deque_push_front(Deque *deque, CST_DEQUE_TYPE value)
{
	struct CstDequeNode *newnode = cqn_create(value, deque->front, NULL);
	deque->front = newnode;
	if (deque->size++) deque->front->next->prev = newnode;
	else deque->back = newnode;
}

void deque_push_back(Deque *deque, CST_DEQUE_TYPE value)
{
	struct CstDequeNode *newnode = cqn_create(value, NULL, deque->back);
	deque->back = newnode;
	if (deque->size++) deque->back->prev->next = newnode;
	else deque->front = newnode;
}

int deque_pop_back(Deque *deque)
{
	if (deque->size)
	{
		struct CstDequeNode *temp = deque->back->prev;
		free(deque->back);
		deque->back = temp;
		if (!--deque->size || deque->size == 1) deque->front = temp;
		if (temp) temp->next = NULL;
		return 0;
	}
	return -1;
}


int deque_pop_front(Deque *deque)
{
	if (deque->size)
	{
		struct CstDequeNode *temp = deque->front->next;
		free(deque->front);
		deque->front = temp;
		if (!--deque->size || deque->size == 1) deque->back = temp;
		if (temp) temp->prev = NULL;
		return 0;
	}
	return -1;
}

Deque deque_copy(Deque *src)
{
        Deque rslt = {0, NULL, NULL};
        for (struct CstDequeNode *i = src->front; i != NULL; i = i->next) deque_push_front(&rslt, i->value);
	return rslt;
}

void deque_destroy(Deque *deque)
{
	deque->size = 0;
	while (deque->back)
	{
		struct CstDequeNode *temp = deque->back;
		deque->back = deque->back->prev;
		free(temp);
	}
	deque->front = NULL;
}

#ifdef __cplusplus
}
#endif

/*
using namespace cst;

void qp(Deque *q)
{
        for (struct CstDequeNode *i = q->front; i != NULL; i = i->next)
        {
                printf("%d", i->value);
                if (i->next) printf("<->");
        }
        putchar(0xa);
}

int main()
{
        Deque q = deque_create();
        deque_push_front(&q, 8);
	qp(&q);
        deque_push_back(&q, 9);
	qp(&q);
        deque_push_front(&q, 10);
        qp(&q);
        Deque c = deque_copy(&q);
        qp(&c);
        deque_pop_back(&c);
        qp(&c);
}
*/
