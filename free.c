#include "malloc.h"

extern heapInfo_t heap;

void free(void *ptr)
{
    if (!ptr)
        return;

    // Recupera il chunk associato al puntatore
    heapChunk_t *chunk = (heapChunk_t *)ptr - 1;
    chunk->inuse = 0;

    // Gestione chunk di grandi dimensioni (> SMALL_MAX)
    if (chunk->size > SMALL_MAX)
    {
        // Rimuovi il chunk dalla lista dei grandi
        heapChunk_t *prev_large = NULL;
        heapChunk_t *current_large = heap.large;
        while (current_large)
        {
            if (current_large == chunk)
            {
                if (prev_large)
                    prev_large->next = current_large->next;
                else
                    heap.large = current_large->next;
                break;
            }
            prev_large = current_large;
            current_large = current_large->next;
        }

        // Dealloca la memoria mappata con munmap
        munmap(chunk, chunk->size + sizeof(heapChunk_t));
        return;
    }

    // Individua la lista corretta (tiny o small) per il chunk
    heapChunk_t *prev = NULL;
    heapChunk_t *current = (chunk->size <= TINY_MAX) ? heap.tiny : heap.small;

    // Itera attraverso la lista per trovare il chunk e fare coalescenza
    while (current)
    {
        if (current == chunk)
        {
            // Coalescenza con il chunk successivo, se è libero
            if (current->next && !current->next->inuse)
            {
                current->size += sizeof(heapChunk_t) + current->next->size;
                current->next = current->next->next;
            }

            // Coalescenza con il chunk precedente, se è libero
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
