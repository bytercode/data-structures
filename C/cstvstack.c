#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef __cplusplus
namespace cst {
#endif

#ifndef CST_VSTACK_TYPE
#define CST_VSTACK_TYPE int
#endif

#ifndef CST_VSTACK_MIN_CAP
#define CST_VSTACK_MIN_CAP 6
#endif

typedef struct VStack
{
        size_t size;
        size_t cap;
        CST_VSTACK_TYPE *arr;
} VStack;

VStack vstack_create()
{
        VStack rslt = {0, CST_VSTACK_MIN_CAP, (CST_VSTACK_TYPE*)malloc(sizeof(CST_VSTACK_TYPE)*CST_VSTACK_MIN_CAP)};
        return rslt;
}

VStack vstack_copy(VStack *src)
{
        VStack rslt = {src->size, src->cap, (CST_VSTACK_TYPE*)malloc(sizeof(CST_VSTACK_TYPE)*src->cap)};
        memcpy(rslt.arr, src->arr, sizeof(CST_VSTACK_TYPE)*src->size);
        return rslt;
}


void vstackp_maybe_realloc(VStack *vstack, size_t addsize)
{
        if (vstack->size+addsize > vstack->cap)
        {
                CST_VSTACK_TYPE *temp = vstack->arr;
                vstack->arr = (CST_VSTACK_TYPE*)malloc(sizeof(CST_VSTACK_TYPE)*pow(2, ceil(log(2)/log(vstack->size+addsize))));
                memcpy(vstack->arr, temp, sizeof(CST_VSTACK_TYPE)*vstack->size);
                free(temp);
        }
}

void vstack_push(VStack *vstack, CST_VSTACK_TYPE val)
{
        vstackp_maybe_realloc(vstack, 1);
        vstack->arr[vstack->size++] = val;
}

int vstack_pop(VStack *vstack)
{
        if (vstack->size == 0) return -1;
        vstack->size--;
        return 0;
}

CST_VSTACK_TYPE *vstack_top(VStack *vstack)
{
	if (vstack->size == 0) return (CST_VSTACK_TYPE*)0;
	return vstack->arr + (vstack->size-1);
}

void vstackp_print(VStack *vstack, const char *fmt, const char *seperator)
{
        putchar('[');
        for (size_t i = 0; i < vstack->size; i++)
        {
                printf(fmt, vstack->arr[i]);
                if (i < vstack->size-1)
                {
                        printf(seperator);
                }
        }
        puts("]");
}

void vstack_destroy(VStack *vstack)
{
        free(vstack->arr);
        vstack->size = 0;
        vstack->cap = 0;
}

#ifdef __cplusplus
}
#endif

int main()
{
	VStack vs = vstack_create();
	vstack_push(&vs, 10);
	VStack cpy = vstack_copy(&vs);
	vstackp_print(&vs, "%d", ", ");
	vstack_pop(&vs);
	vstackp_print(&vs, "%d", ", ");
	vstackp_print(&cpy, "%d", ", ");
	
	vstack_destroy(&vs);
	return 0;
}
