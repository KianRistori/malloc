#include "../include/malloc.h"

extern heapInfo_t	heap;

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

void	free_chunk_in_zone(heapZone_t *heap, heapChunk_t *zone, heapChunk_t *chunk, size_t size)
{
	free_chunk(zone, chunk);
	if (heap->allocation_count > 1024)
	{
		if (is_zone_empty(zone))
		{
			munmap(zone->original_ptr, size);
			heap->start = NULL;
		}
		heap->allocation_count = 0;
	}
}

void	free(void *ptr)
{
	if (!ptr)
		return;

	heapChunk_t *chunk = (heapChunk_t *)((char *)ptr - sizeof(heapChunk_t));

	if (chunk->size <= TINY_MAX)
		free_chunk_in_zone(heap.tiny, heap.tiny->start, chunk, TINY_ALLOCATE);
	else if (chunk->size <= SMALL_MAX)
		free_chunk_in_zone(heap.small, heap.small->start, chunk, SMALL_ALLOCATE);
	else
		free_chunk_in_zone(heap.large, heap.large->start, chunk, LARGE_ALLOCATE);
}
