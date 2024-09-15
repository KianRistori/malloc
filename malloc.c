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

int	initHeap()
{
	size_t tiny_zone_size = getpagesize();
	size_t small_zone_size = getpagesize() * 4;

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
	heap.large = NULL;

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

void free(void *ptr)
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

void	*realloc(void *ptr, size_t size)
{
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    if (ptr == NULL) {
        return malloc(size);
    }

	heapChunk_t *chunk = (heapChunk_t *)ptr - 1;
	 if (ptr != chunk->original_ptr) {
        return NULL;
    }

    if (size <= chunk->size) {
		if (chunk->size > size + sizeof(heapChunk_t)) {
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

	if (next && !next->inuse && (chunk->size + sizeof(heapChunk_t) + next->size >= size)) {
        size_t total_size = chunk->size + sizeof(heapChunk_t) + next->size;

        if (total_size > size + sizeof(heapChunk_t)) {
            heapChunk_t *new_chunk = (heapChunk_t *)((char *)chunk + sizeof(heapChunk_t) + size);
            new_chunk->size = total_size - size - sizeof(heapChunk_t);
            new_chunk->inuse = 0;
            new_chunk->next = next->next;
            chunk->next = new_chunk;
        } else
            chunk->next = next->next;
        chunk->size = size;
        return ptr;
    }

    void *new_ptr = malloc(size);
    if (!new_ptr) {
        return NULL;
    }

    ft_memcpy(new_ptr, ptr, chunk->size);
    free(ptr);
    return new_ptr;
}