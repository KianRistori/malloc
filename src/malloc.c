#include "../include/malloc.h"

heapInfo_t	heap = {NULL, NULL, NULL};

void	*allocate_zone(size_t size)
{
	void *start = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (start == MAP_FAILED)
	{
		perror("mmap");
		return NULL;
	}
	return start;
}

void	init_heap_zone_start(heapChunk_t **zone, size_t zone_size)
{
	*zone = allocate_zone(zone_size);
	if (!*zone)
		return;

	(*zone)->size = zone_size - sizeof(heapChunk_t);
	(*zone)->inuse = 0;
	(*zone)->next = NULL;
	(*zone)->original_ptr = *zone;
}

int	init_heap(size_t size)
{
	size_t tiny_zone_size = TINY_ALLOCATE;
	size_t small_zone_size = SMALL_ALLOCATE;
	size_t large_zone_size = LARGE_ALLOCATE;

	if (size <= TINY_MAX && heap.tiny == NULL)
	{
		heap.tiny = allocate_zone(tiny_zone_size);
		if (!heap.tiny)
			return 1;

		init_heap_zone_start(&heap.tiny->start, tiny_zone_size);
	}

	if (size <= SMALL_MAX && heap.small == NULL)
	{
		heap.small = allocate_zone(small_zone_size);
		if (!heap.small)
			return 1;

		init_heap_zone_start(&heap.small->start, small_zone_size);
	}

	if (size > SMALL_MAX && heap.large == NULL)
	{
		heap.large = allocate_zone(large_zone_size);
		if (!heap.large)
			return 1;

		init_heap_zone_start(&heap.large->start, large_zone_size);
	}

	return 0;
}

heapChunk_t	*extend_zone(size_t zone_size)
{
	heapChunk_t *new_zone = allocate_zone(zone_size);
	if (!new_zone)
		return NULL;

	new_zone->size = zone_size - sizeof(heapChunk_t);
	new_zone->inuse = 0;
	new_zone->next = NULL;

	return new_zone;
}

void	*malloc(size_t size)
{
	heapChunk_t *chunk = NULL;
	heapChunk_t **heap_zone = NULL;
	size_t zone_size = 0;

	if (size <= TINY_MAX)
	{
		if (heap.tiny == NULL && init_heap(size))
			return NULL;
		chunk = heap.tiny->start;
		heap_zone = &heap.tiny->start;
		zone_size = TINY_ALLOCATE;
		heap.tiny->allocation_count++;
	}
	else if (size <= SMALL_MAX)
	{
		if (heap.small == NULL && init_heap(size))
			return NULL;
		chunk = heap.small->start;
		heap_zone = &heap.small->start;
		zone_size = SMALL_ALLOCATE;
		heap.small->allocation_count++;
	}
	else
	{
		if (heap.large == NULL && init_heap(size))
			return NULL;
		chunk = heap.large->start;
		heap_zone = &heap.large->start;
		zone_size = LARGE_ALLOCATE;
		heap.large->allocation_count++;
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
