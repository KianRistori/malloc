#include "malloc.h"

heapInfo_t heap = {NULL, NULL, NULL};

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

int	initHeap()
{
	size_t tiny_zone_size = getpagesize();
	size_t small_zone_size = getpagesize() * 4;
	size_t large_zone_size = getpagesize() * 16;

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
	heap.large->size = LARGE_MAX - sizeof(heapChunk_t);
	heap.large->inuse = 0;
	heap.large->next = NULL;

	return 0;
}

void	*malloc(size_t size) 
{
	if (heap.tiny == NULL && initHeap() != 0)
		return NULL; 

	heapChunk_t *chunk = NULL;

	if (size <= TINY_MAX)
		chunk = heap.tiny;
	else if (size <= SMALL_MAX)
		chunk = heap.small;
	else if (size <= LARGE_MAX)
		chunk = heap.large;
	else
	{
		size_t large_size = size + sizeof(heapChunk_t);
		chunk = allocate_zone(large_size);
		if (!chunk)
			return NULL;

		chunk->size = size;
		chunk->inuse = 1;
		chunk->next = heap.large;
		heap.large = chunk;
		chunk->original_ptr = (void *)(chunk + 1);
		return (void *)(chunk + 1);
	}

	while (chunk && (chunk->inuse || chunk->size < size))
		chunk = chunk->next;

	if (!chunk)
		return NULL;

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
	chunk->original_ptr = (void *)(chunk + 1);
	return (void *)(chunk + 1);
}

