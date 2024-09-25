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

void	free(void *ptr)
{
    if (!ptr)
        return;

    heapChunk_t *chunk = (heapChunk_t *)((char *)ptr - sizeof(heapChunk_t));

    // Controlla se il chunk appartiene alla zona tiny
    heapChunk_t *tiny_zone = heap.tiny;
    heapChunk_t *prev_tiny = NULL;
    while (tiny_zone)
    {
        if (chunk >= tiny_zone && chunk < (heapChunk_t *)((char *)tiny_zone + getpagesize()))
        {
            chunk->inuse = 0; // Marca il chunk come libero
            if (is_zone_empty(tiny_zone))
            {
                // Dealloca l'intera zona con munmap
                if (prev_tiny)
                    prev_tiny->next = tiny_zone->next;
                else
                    heap.tiny = tiny_zone->next;

                if (munmap(tiny_zone, getpagesize()) != 0)
                {
                    perror("munmap");
                }
            }
            return;
        }
        prev_tiny = tiny_zone;
        tiny_zone = tiny_zone->next;
    }

    // Controlla se il chunk appartiene alla zona small
    heapChunk_t *small_zone = heap.small;
    heapChunk_t *prev_small = NULL;
    while (small_zone)
    {
        if (chunk >= small_zone && chunk < (heapChunk_t *)((char *)small_zone + getpagesize() * 4))
        {
            chunk->inuse = 0; // Marca il chunk come libero
            if (is_zone_empty(small_zone))
            {
                // Dealloca l'intera zona con munmap
                if (prev_small)
                    prev_small->next = small_zone->next;
                else
                    heap.small = small_zone->next;

                if (munmap(small_zone, getpagesize() * 4) != 0)
                {
                    perror("munmap");
                }
            }
            return;
        }
        prev_small = small_zone;
        small_zone = small_zone->next;
    }

    // Controlla se il chunk appartiene alla zona large
    heapChunk_t *large_zone = heap.large;
    heapChunk_t *prev_large = NULL;
    while (large_zone)
    {
        if (chunk == large_zone)
        {
            // Dealloca l'intero chunk con munmap
            if (prev_large)
                prev_large->next = large_zone->next;
            else
                heap.large = large_zone->next;

            if (munmap(large_zone, large_zone->size + sizeof(heapChunk_t)) != 0)
            {
                perror("munmap");
            }
            return;
        }
        prev_large = large_zone;
        large_zone = large_zone->next;
    }
}

