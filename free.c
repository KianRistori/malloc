#include "malloc.h"

extern heapInfo_t heap;

int	is_zone_empty(heapChunk_t *zone)
{
	heapChunk_t *chunk = zone;
	while (chunk)
	{
		if (chunk->inuse)
			return 0;
		chunk = chunk->next;
	}
	return 1;
}


void	free_chunk(heapChunk_t *zone, heapChunk_t *chunk)
{
	heapChunk_t *start = zone;
	while (zone)
	{
		if (chunk == zone)
		{
			chunk->inuse = 0;

			if (chunk->next && chunk->next->inuse == 0)
			{
				chunk->size += sizeof(heapChunk_t) + chunk->next->size;
				chunk->next = chunk->next->next;
			}

			if (zone != start)
			{
				heapChunk_t *prev = start;
				while (prev && prev->next != chunk)
					prev = prev->next;

				if (prev && prev->inuse == 0)
				{
					prev->size += sizeof(heapChunk_t) + chunk->size;
					prev->next = chunk->next;
					chunk = prev;
				}
			}
			return;  	
		}
		zone = zone->next;
	}
	zone = start;
}


void free(void *ptr)
{
	if (!ptr)
        return;

    heapChunk_t *chunk = (heapChunk_t *)((char *)ptr - sizeof(heapChunk_t));

    if (chunk->size <= TINY_MAX)
    {
        free_chunk(heap.tiny, chunk);
        if (heap.tiny_allocation_count > 1024)
        {
            if (is_zone_empty(heap.tiny))
            {
                munmap(heap.tiny->original_ptr, TINY_ALLOCATE);
                heap.tiny = NULL;
            }
			heap.tiny_allocation_count = 0;
        }
    }
    else if (chunk->size <= SMALL_MAX)
    {
        free_chunk(heap.small, chunk);
        if (heap.small_allocation_count > 1024)
        {
            if (is_zone_empty(heap.small))
            {
                munmap(heap.small->original_ptr, SMALL_ALLOCATE);
                heap.small = NULL;
            }
			heap.small_allocation_count = 0;
        }
    }
    else
    {
        free_chunk(heap.large, chunk);
        if (heap.large_allocation_count > 1024)
        {
            if (is_zone_empty(heap.large))
            {
                munmap(heap.large->original_ptr, LARGE_ALLOCATE);
                heap.large = NULL;
            }
			heap.large_allocation_count = 0;
        }
    }
}
