#include <stdlib.h>
#include <string.h>

#define nil ((void*)0)
typedef unsigned long ulong;

void*
mallocz(ulong size, int clr)
{
	void *v;

	v = malloc(size);
	if(clr && v != nil)
		memset(v, 0, size);
	return v;
}

