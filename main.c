#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
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

int	initHeap(heapInfo_t *heap)
{
	size_t tiny_zone_size = getpagesize();  // Una zona per allocazioni TINY
	size_t small_zone_size = getpagesize() * 4;  // Una zona per allocazioni SMALL

	heap->tiny = allocate_zone(tiny_zone_size);
	if (!heap->tiny)
		return 1;

	heap->tiny->size = tiny_zone_size - sizeof(heapChunk_t);
	heap->tiny->inuse = 0;
	heap->tiny->next = NULL;

	heap->small = allocate_zone(small_zone_size);
	if (!heap->small)
		return 1;
	heap->small->size = small_zone_size - sizeof(heapChunk_t);
	heap->small->inuse = 0;
	heap->small->next = NULL;

	heap->large = NULL;  // Gestione delle allocazioni LARGE sarà fatta al momento

	return 0;
}

void	*malloc(size_t size) 
{
	if (heap.tiny == NULL && initHeap(&heap) != 0)
		return NULL; 

	heapChunk_t *chunk = NULL;
	
	if (size <= 0)
		return NULL;

	if (size <= TINY_MAX)
		chunk = heap.tiny;
	else if (size <= SMALL_MAX)
		chunk = heap.small;
	else
	{
		// LARGE allocation, directly use mmap
		size_t large_size = size + sizeof(heapChunk_t);
		chunk = allocate_zone(large_size);
		if (!chunk)
			return NULL;

		chunk->size = size;
		chunk->inuse = 1;
		chunk->next = heap.large;
		heap.large = chunk;
		return (void *)(chunk + 1);
	}

	// TINY and SMALL allocation logic
	while (chunk && (chunk->inuse || chunk->size < size))
		chunk = chunk->next;

	if (!chunk)
		return NULL;  // No available chunk found

	if (chunk->size > size + sizeof(heapChunk_t))
	{
		// Split the chunk
		heapChunk_t *new_chunk = (heapChunk_t *)((char *)chunk + sizeof(heapChunk_t) + size);
		new_chunk->size = chunk->size - size - sizeof(heapChunk_t);
		new_chunk->inuse = 0;
		new_chunk->next = chunk->next;
		chunk->size = size;
		chunk->next = new_chunk;
	}

	chunk->inuse = 1;
	return (void *)(chunk->next);
}

void free(void *ptr)
{
	if (!ptr)
		return;

	heapChunk_t *chunk = (heapChunk_t *)ptr - 1;
	chunk->inuse = 0;

	// If it's a LARGE allocation, free it with munmap
	if (chunk->size > SMALL_MAX)
		munmap(chunk, chunk->size + sizeof(heapChunk_t));
	// TINY and SMALL blocks will be reused, so just mark them as free
}

