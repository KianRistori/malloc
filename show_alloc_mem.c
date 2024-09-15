#include "malloc.h"

// Helper function to write a string to stdout
void ft_putstr(const char *str) {
    while (*str) {
        write(1, str, 1);
        str++;
    }
}

// Helper function to convert a number to a string in hexadecimal
void ft_putnbr_base(unsigned long nbr, const char *base) {
    if (nbr >= 16)
        ft_putnbr_base(nbr / 16, base);
    write(1, &base[nbr % 16], 1);
}

// Helper function to write a number as a decimal string
void ft_putnbr(size_t nbr) {
    if (nbr >= 10)
        ft_putnbr(nbr / 10);
    char c = (nbr % 10) + '0';
    write(1, &c, 1);
}

// Function to print each chunk's memory info
void print_chunk(heapChunk_t *chunk_list, const char *zone_name) {
    heapChunk_t *chunk = chunk_list;
    int first = 1;

    while (chunk) {
        if (chunk->inuse) {
            if (first) {
                // Print zone name only once, when the first chunk is found
                ft_putstr(zone_name);
                ft_putstr(" : 0x");
                ft_putnbr_base((unsigned long)chunk, "0123456789ABCDEF");
                ft_putstr("\n");
                first = 0;
            }
            // Print start address
            ft_putstr("0x");
            ft_putnbr_base((unsigned long)chunk, "0123456789ABCDEF");

            ft_putstr(" - 0x");

            // Print end address (start + size)
            ft_putnbr_base((unsigned long)((char*)chunk + chunk->size), "0123456789ABCDEF");

            // Print size in bytes
            ft_putstr(" : ");
            ft_putnbr(chunk->size);
            ft_putstr(" bytes\n");
        }
        chunk = chunk->next;
    }
}

// Function to show the state of the allocated memory zones
void show_alloc_mem() {
    extern heapInfo_t heap;  // Global heap info

    size_t total_size = 0;

    // Print all TINY chunks
    if (heap.tiny) {
        print_chunk(heap.tiny, "TINY");
        // Sum up total for TINY
        heapChunk_t *chunk = heap.tiny;
        while (chunk) {
            if (chunk->inuse)
                total_size += chunk->size;
            chunk = chunk->next;
        }
    }

    // Print all SMALL chunks
    if (heap.small) {
        print_chunk(heap.small, "SMALL");
        // Sum up total for SMALL
        heapChunk_t *chunk = heap.small;
        while (chunk) {
            if (chunk->inuse)
                total_size += chunk->size;
            chunk = chunk->next;
        }
    }

    // Print all LARGE chunks
    if (heap.large) {
        print_chunk(heap.large, "LARGE");
        // Sum up total for LARGE
        heapChunk_t *chunk = heap.large;
        while (chunk) {
            if (chunk->inuse)
                total_size += chunk->size;
            chunk = chunk->next;
        }
    }

    // Print total memory used
    ft_putstr("Total : ");
    ft_putnbr(total_size);
    ft_putstr(" bytes\n");
}

