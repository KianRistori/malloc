#include "malloc.h"

void *realloc(void *ptr, size_t size)
{
    // Se ptr è NULL, comportarsi come malloc
    if (!ptr)
        return malloc(size);

    // Se size è 0, comportarsi come free
    if (size == 0)
    {
        free(ptr);
        return NULL;
    }

    heapChunk_t *chunk = (heapChunk_t *)((char *)ptr - sizeof(heapChunk_t));
    
    // Se la nuova dimensione è minore o uguale alla dimensione attuale
    if (size <= chunk->size)
    {
        // Se il chunk ha spazio extra, riduci e crea un nuovo chunk libero
        if (chunk->size > size + sizeof(heapChunk_t))
        {
            heapChunk_t *new_chunk = (heapChunk_t *)((char *)chunk + sizeof(heapChunk_t) + size);
            new_chunk->size = chunk->size - size - sizeof(heapChunk_t);
            new_chunk->inuse = 0;
            new_chunk->next = chunk->next;
            chunk->size = size;
            chunk->next = new_chunk;
        }
        return ptr;
    }

    // Se la dimensione richiesta è maggiore
    heapChunk_t *next_chunk = chunk->next;
    
    // Verifica se il chunk successivo è libero e ha abbastanza spazio
    if (next_chunk && !next_chunk->inuse && chunk->size + sizeof(heapChunk_t) + next_chunk->size >= size)
    {
        // Espandi il chunk corrente
        chunk->size += sizeof(heapChunk_t) + next_chunk->size;
        chunk->next = next_chunk->next;
        
        // Verifica se c'è spazio extra da creare un nuovo chunk libero
        if (chunk->size > size + sizeof(heapChunk_t))
        {
            heapChunk_t *new_chunk = (heapChunk_t *)((char *)chunk + sizeof(heapChunk_t) + size);
            new_chunk->size = chunk->size - size - sizeof(heapChunk_t);
            new_chunk->inuse = 0;
            new_chunk->next = chunk->next;
            chunk->size = size;
            chunk->next = new_chunk;
        }
        return ptr;
    }

    // Altrimenti, dobbiamo allocare un nuovo chunk
    void *new_ptr = malloc(size);
    if (!new_ptr)
        return NULL;

    // Copia i dati dalla vecchia memoria a quella nuova
    ft_memcpy(new_ptr, ptr, chunk->size);
    free(ptr); // Libera il vecchio chunk

    return new_ptr;
}
