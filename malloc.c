#include "malloc.h"

heapInfo_t heap = {NULL, NULL, NULL};

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

int initHeap()
{
    size_t tiny_zone_size = TINY_ALLOCATE;
    size_t small_zone_size = SMALL_ALLOCATE; 
    size_t large_zone_size = LARGE_ALLOCATE;

    heap.tiny = allocate_zone(tiny_zone_size);
    if (!heap.tiny)
        return 1;

    heap.tiny->size = tiny_zone_size - sizeof(heapChunk_t);
    heap.tiny->inuse = 0;
    heap.tiny->next = NULL;

    heap.small = allocate_zone(small_zone_size);
    if (!heap.small)
        return 1;

    heap.small->size = small_zone_size - sizeof(heapChunk_t);
    heap.small->inuse = 0;
    heap.small->next = NULL;

    heap.large = allocate_zone(large_zone_size);
    if (!heap.large)
        return 1;

    heap.large->size = large_zone_size - sizeof(heapChunk_t);
    heap.large->inuse = 0;
    heap.large->next = NULL;

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
    if (heap.tiny == NULL && initHeap() != 0)
        return NULL;

    heapChunk_t *chunk = NULL;
    heapChunk_t **heap_zone = NULL;
    size_t zone_size = 0;

    if (size <= TINY_MAX)
    {
        chunk = heap.tiny;
        heap_zone = &heap.tiny;
        zone_size = TINY_ALLOCATE; 
    }
    else if (size <= SMALL_MAX)
    {
        chunk = heap.small;
        heap_zone = &heap.small;
        zone_size = SMALL_ALLOCATE;
    }
    else
    {
        chunk = heap.large;
        heap_zone = &heap.large;
        zone_size = LARGE_ALLOCATE;
    }

    // Cerca un chunk libero nella zona corrente
    while (chunk && (chunk->inuse || chunk->size < size))
        chunk = chunk->next;

    // Se non ci sono chunk disponibili, estendi la zona
    if (!chunk)
    {
        heapChunk_t *new_zone = extend_zone(zone_size);
        if (!new_zone)
            return NULL;

        // Collegalo alla fine della lista di chunk della zona
        heapChunk_t *last = *heap_zone;
        while (last->next != NULL)
            last = last->next;
        last->next = new_zone;
        chunk = new_zone;
    }

    // Se il chunk è troppo grande, dividilo
    if (chunk->size > size + sizeof(heapChunk_t))
    {
        heapChunk_t *new_chunk = (heapChunk_t *)((char *)chunk + sizeof(heapChunk_t) + size);
        new_chunk->size = chunk->size - size - sizeof(heapChunk_t);
        new_chunk->inuse = 0;
        new_chunk->next = chunk->next;
        chunk->size = size;
        chunk->next = new_chunk;
    }

    // Marca il chunk come in uso e restituiscilo
    chunk->inuse = 1;
    chunk->original_ptr = (void *)(chunk + 1);
    return (void *)(chunk + 1);
}

