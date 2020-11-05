#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1<->2<->3<->5
// Back = 1
// Front = 5

#ifndef CST_QUEUE_TYPE
#define CST_QUEUE_TYPE int
#endif

#ifdef __cplusplus
namespace cst {
#endif

struct CstQueueNode
{
	CST_QUEUE_TYPE value;
	struct CstQueueNode *next;
	struct CstQueueNode *prev;
};

struct CstQueueNode *cqn_create(CST_QUEUE_TYPE value, struct CstQueueNode *next, struct CstQueueNode *prev)
{
	struct CstQueueNode *rslt =(struct CstQueueNode*) malloc(sizeof(struct CstQueueNode));
	rslt->value = value;
	rslt->next = next;
	rslt->prev = prev;
	return rslt;
}

typedef struct Queue
{
	size_t size;
	struct CstQueueNode *back;
	struct CstQueueNode *front;
} Queue;

Queue queue_create()
{
	Queue rslt = {0, NULL, NULL};
	return rslt;
}

void queue_push(Queue *queue, CST_QUEUE_TYPE value)
{
	struct CstQueueNode *newnode = cqn_create(value, NULL, queue->back);
	queue->back = newnode;
	if (queue->size++) queue->back->prev->next = newnode;
	else queue->front = newnode;
}

int queue_pop(Queue *queue)
{
	if (queue->size)
	{
		struct CstQueueNode *temp = queue->front->next;
		free(queue->front);
		queue->front = temp;
		if (!--queue->size || queue->size == 1) queue->back = temp;
		if (temp) temp->prev = NULL;
		return 0;
	}
	return -1;
}

Queue queue_copy(Queue *src)
{
        Queue rslt = {0, NULL, NULL};
        for (struct CstQueueNode *i = src->front; i != NULL; i = i->next) queue_push(&rslt, i->value);
	return rslt;
}

void queue_destroy(Queue *queue)
{
	queue->size = 0;
	while (queue->back)
	{
		struct CstQueueNode *temp = queue->back;
		queue->back = queue->back->prev;
		free(temp);
	}
	queue->front = NULL;
}

#ifdef __cplusplus
}
#endif
/*
using namespace cst;

void qp(Queue *q)
{
	for (struct CstQueueNode *i = q->front; i != NULL; i = i->next)
	{
		printf("%d", i->value);
		if (i->next) printf("<->");
	}
	putchar(0xa);
}

int main()
{
	Queue q = queue_create();
	queue_push(&q, 8);
	queue_push(&q, 9);
	queue_push(&q, 10);
	qp(&q);
	Queue c = queue_copy(&q);
	qp(&c);
	queue_pop(&c);
	qp(&c);
	queue_pop(&c);
	qp(&c);
	queue_pop(&c);
	qp(&c);

	queue_destroy(&q);
	queue_destroy(&c);
	return 0;
}
*/
