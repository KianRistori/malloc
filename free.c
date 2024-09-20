#include "malloc.h"

extern heapInfo_t	heap;

void	free(void *ptr)
{
	if (!ptr)
		return;

	heapChunk_t *chunk = (heapChunk_t *)ptr - 1;
	chunk->inuse = 0;

	if (chunk->size > SMALL_MAX)
	{
		munmap(chunk, chunk->size + sizeof(heapChunk_t));
		return;
	}

	heapChunk_t *prev = NULL;
	heapChunk_t *current = (chunk->size <= TINY_MAX) ? heap.tiny : heap.small;

	while (current)
	{
		if (current == chunk)
		{
			if (current->next && !current->next->inuse)
			{
				current->size += sizeof(heapChunk_t) + current->next->size;
				current->next = current->next->next;
			}
			if (prev && !prev->inuse)
			{
				prev->size += sizeof(heapChunk_t) + current->size;
				prev->next = current->next;
				current = prev;
			}
			break;
		}
		prev = current;
		current = current->next;
	}
}
