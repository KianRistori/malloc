#include "../include/malloc.h"

void *realloc(void *ptr, size_t size)
{
	if (!ptr)
		return malloc(size);

	heapChunk_t *chunk = (heapChunk_t *)((char *)ptr - sizeof(heapChunk_t));
	if (size == 0)
	{
		free(ptr);
		return NULL;
	}

	if (size <= chunk->size)
		return ptr;

	void *new_ptr = malloc(size);
	if (!new_ptr)
		return NULL;

	ft_memcpy(new_ptr, ptr, chunk->size);
	free(ptr);
	return new_ptr;
}