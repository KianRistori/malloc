#include "malloc.h"

heapInfo_t heap = {NULL, NULL, NULL, 0, 0, 0};

void *allocate_zone(size_t size)
{
    void *start = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (start == MAP_FAILED)
    {
        perror("mmap");
        return NULL;
    }
    return start;
}

int initHeap(size_t size)
{
    size_t tiny_zone_size = TINY_ALLOCATE;
    size_t small_zone_size = SMALL_ALLOCATE; 
    size_t large_zone_size = LARGE_ALLOCATE;

    if (size <= TINY_MAX && heap.tiny == NULL)
    {
        heap.tiny = allocate_zone(tiny_zone_size);
        if (!heap.tiny)
            return 1;

        heap.tiny->size = tiny_zone_size - sizeof(heapChunk_t);
        heap.tiny->inuse = 0;
        heap.tiny->next = NULL;
        heap.tiny->original_ptr = heap.tiny;
    }

    if (size <= SMALL_MAX && heap.small == NULL)
    {
        heap.small = allocate_zone(small_zone_size);
        if (!heap.small)
            return 1;

        heap.small->size = small_zone_size - sizeof(heapChunk_t);
        heap.small->inuse = 0;
        heap.small->next = NULL;
        heap.small->original_ptr = heap.small;
    }

    if (size > SMALL_MAX && heap.large == NULL)
    {
        heap.large = allocate_zone(large_zone_size);
        if (!heap.large)
            return 1;

        heap.large->size = large_zone_size - sizeof(heapChunk_t);
        heap.large->inuse = 0;
        heap.large->next = NULL;
        heap.large->original_ptr = heap.large;
    }

    return 0;
}

heapChunk_t *extend_zone(size_t zone_size)
{
    heapChunk_t *new_zone = allocate_zone(zone_size);
    if (!new_zone)
        return NULL;

    new_zone->size = zone_size - sizeof(heapChunk_t);
    new_zone->inuse = 0;
    new_zone->next = NULL;

    return new_zone;
}

void *malloc(size_t size)
{
    heapChunk_t *chunk = NULL;
    heapChunk_t **heap_zone = NULL;
    size_t zone_size = 0;

    if (size <= TINY_MAX)
    {
        if (heap.tiny == NULL && initHeap(size))
            return NULL;
        chunk = heap.tiny;
        heap_zone = &heap.tiny;
        zone_size = TINY_ALLOCATE;
        heap.tiny_allocation_count++;
    }
    else if (size <= SMALL_MAX)
    {
        if (heap.small == NULL && initHeap(size))
            return NULL;
        chunk = heap.small;
        heap_zone = &heap.small;
        zone_size = SMALL_ALLOCATE;
        heap.small_allocation_count++;
    }
    else
    {
        if (heap.large == NULL && initHeap(size))
            return NULL;
        chunk = heap.large;
        heap_zone = &heap.large;
        zone_size = LARGE_ALLOCATE;
        heap.large_allocation_count++;
    }

    while (chunk && (chunk->inuse || chunk->size < size))
        chunk = chunk->next;

    if (!chunk)
    {
        heapChunk_t *new_zone = extend_zone(zone_size);
        
        heapChunk_t *last = *heap_zone;
        while (last->next != NULL)
            last = last->next;
        last->next = new_zone;
        chunk = new_zone;
    }

    if (chunk->size > size + sizeof(heapChunk_t))
    {
        heapChunk_t *new_chunk = (heapChunk_t *)((char *)chunk + sizeof(heapChunk_t) + size);
        new_chunk->size = chunk->size - size - sizeof(heapChunk_t);
        new_chunk->inuse = 0;
        new_chunk->next = chunk->next;
        chunk->size = size;
        chunk->next = new_chunk;
    }


    chunk->inuse = 1;
    return (void *)(chunk + 1);
}
