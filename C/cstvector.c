#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef __cplusplus
namespace cst {
#endif

#ifndef CST_VECTOR_TYPE
#define CST_VECTOR_TYPE int
#endif

#ifndef CST_VECTOR_MIN_CAP
#define CST_VECTOR_MIN_CAP 6
#endif

typedef struct Vector
{
	size_t size;
	size_t cap;
	CST_VECTOR_TYPE *arr;
} Vector;

Vector vector_create()
{
	Vector rslt = {0, CST_VECTOR_MIN_CAP, (CST_VECTOR_TYPE*)malloc(sizeof(CST_VECTOR_TYPE)*CST_VECTOR_MIN_CAP)};
	return rslt;
}

Vector vector_copy(Vector *src)
{
	Vector rslt = {src->size, src->cap, (CST_VECTOR_TYPE*)malloc(sizeof(CST_VECTOR_TYPE)*src->cap)};
	memcpy(rslt.arr, src->arr, sizeof(CST_VECTOR_TYPE)*src->size);
	return rslt;
}

void vectorp_maybe_realloc(Vector *vec, size_t addsize)
{
	if (vec->size+addsize > vec->cap)
	{
		CST_VECTOR_TYPE *temp = vec->arr;
		vec->arr = (CST_VECTOR_TYPE*)malloc(sizeof(CST_VECTOR_TYPE*)*(vec->cap = pow(2, ceil(log(2)/log(vec->size+addsize)))));
		memcpy(vec->arr, temp, sizeof(CST_VECTOR_TYPE)*vec->size);
		free(temp);
	}
}

void vector_push_back(Vector *vec, CST_VECTOR_TYPE val)
{
	vectorp_maybe_realloc(vec, 1);
	vec->arr[vec->size++] = val;
}

int vector_pop_back(Vector *vec)
{
	if (vec->size == 0) return -1;
	vec->size--;
	return 0;
}

int vector_insert(Vector *vec, CST_VECTOR_TYPE val, size_t index)
{
	if (index > vec->size) return -1;
	vectorp_maybe_realloc(vec, 1);
	memmove((void*)(vec->arr+index+1), (void*)(vec->arr+index), sizeof(CST_VECTOR_TYPE*)*(vec->size-index));
	vec->arr[index] = val;
	vec->size++;
	return 0;
}

int vector_insert_array(Vector *vec, CST_VECTOR_TYPE *array, size_t arrlen, size_t index)
{
	if (index > vec->size) return -1;
	vectorp_maybe_realloc(vec, arrlen);
	memmove((void*)(vec->arr+index+arrlen), (void*)(vec->arr+index), sizeof(CST_VECTOR_TYPE)*(vec->size-index));
	memmove((void*)(vec->arr+index), (void*)array, sizeof(CST_VECTOR_TYPE)*arrlen);
	vec->size += arrlen;
	return 0;
}

int vector_erase(Vector *vec, size_t at)
{
	if (at > vec->size) return -1;
	memmove((void*)(vec->arr+at), (void*)(vec->arr+at+1),  sizeof(CST_VECTOR_TYPE)*((vec->size--)-at-1));
	return 0;
}

int vector_erase_size(Vector *vec, size_t index, size_t size)
{
	if (index >= vec->size || index+size > vec->size) return -1;
	memmove((void*)(vec->arr+index), (void*)(vec->arr+index+size), sizeof(CST_VECTOR_TYPE)*(vec->size-index-size));
	vec->size -= size;
	return 0;
}

int vector_erase_range(Vector *vec, size_t start, size_t end)
{
	if (start > end) return -1;
	return vector_erase_size(vec, start, end-start);
}

void vectorp_print(Vector *vec, const char *fmt, const char *seperator)
{
	putchar('[');
	for (size_t i = 0; i < vec->size; i++)
	{
		printf(fmt, vec->arr[i]);
		if (i < vec->size-1)
		{
			printf(seperator);
		}
	}
	puts("]");
}

#ifdef __cplusplus
}
#endif

#ifdef CST_VECTOR_SHORT_FN
#define vpb(v, va) vector_push_back(v, va)
#define vppb(v) vector_pop_back(v)
#define vi(v, e, i) vector_insert(v, e, i)
#define via(v, a, l, i) vector_insert_array(v, a, l, i)
#define ve(v, i) vector_erase(v, i)
#define ves(v, i, s) vector_erase_size(v, i, s)
#define ver(v, s, e) vector_erase_range(v, s, e)
#define vpp(v, f, s) vectorp_print(v, f, s)
#endif
