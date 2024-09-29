#ifndef MALLOC_H
# define MALLOC_H

# include <stdio.h>
# include <sys/mman.h>
# include <unistd.h>
# include <stdint.h>
# include "../libft/libft.h"

#define TINY_MAX (64 * 1024)				// 64 KB
#define SMALL_MAX (1024 * 1024)				// 1 MB

#define TINY_ALLOCATE (1024 * 64)			// 64 KB
#define SMALL_ALLOCATE (1024 * 1024)		// 1 MB
#define LARGE_ALLOCATE (1024 * 1024 * 256)	//256 MB

typedef struct heapChunk {
	size_t size;
	int inuse;
	void *original_ptr;
	struct heapChunk *next;
} heapChunk_t;

typedef struct heapZone {
	heapChunk_t *start;
	size_t allocation_count;
} heapZone_t;

typedef struct {
	heapZone_t *tiny;
	heapZone_t *small;
	heapZone_t *large;
} heapInfo_t;

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem();

#endif