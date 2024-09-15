#ifndef MALLOC_H
# define MALLOC_H

# include "libft/libft.h"

#define TINY_MAX 64
#define SMALL_MAX 512

typedef struct heapChunk {
	size_t size;
	int inuse;
	void *original_ptr;
	struct heapChunk *next;
} heapChunk_t;

typedef struct {
	heapChunk_t *tiny;
	heapChunk_t *small;
	heapChunk_t *large;
} heapInfo_t;

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

#endif
