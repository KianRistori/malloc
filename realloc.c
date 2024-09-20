#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
    if (size == 0)
    {
        free(ptr);
        return NULL;
    }

    if (!ptr)
    {
        return malloc(size);
    }

	heapChunk_t *chunk = (heapChunk_t *)ptr - 1;
	if (ptr != chunk->original_ptr)
        return NULL;

	if (size <= chunk->size)
	{
		if (chunk->size > size + sizeof(heapChunk_t))
		{
            heapChunk_t *new_chunk = (heapChunk_t *)((char *)chunk + sizeof(heapChunk_t) + size);
			new_chunk->size = chunk->size - size - sizeof(heapChunk_t);
			new_chunk->inuse = 0;
			new_chunk->next = chunk->next;
			chunk->size = size;
			chunk->next = new_chunk;
		}
		return ptr;
	}


	heapChunk_t *next = chunk->next;

	if (next && !next->inuse && (chunk->size + sizeof(heapChunk_t) + next->size >= size))
    {
        size_t total_size = chunk->size + sizeof(heapChunk_t) + next->size;

        if (total_size > size + sizeof(heapChunk_t))
        {
            heapChunk_t *new_chunk = (heapChunk_t *)((char *)chunk + sizeof(heapChunk_t) + size);
            new_chunk->size = total_size - size - sizeof(heapChunk_t);
            new_chunk->inuse = 0;
            new_chunk->next = next->next;
            chunk->next = new_chunk;
        }
        else
            chunk->next = next->next;

        chunk->size = size;
        return ptr;
    }

    void *new_ptr = malloc(size);
    if (!new_ptr)
        return NULL;

    ft_memcpy(new_ptr, ptr, chunk->size);
    free(ptr);
    return new_ptr;
}
