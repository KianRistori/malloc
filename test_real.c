#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definizione semplificata di ft_memcpy per copiare dati
void *ft_memcpy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}

int main() {
    // Scenario 1: Riallocare un blocco con memoria maggiore
    char *p1 = malloc(32); // Allocazione iniziale di 32 byte
    if (!p1) { printf("malloc failed\n"); return 1; }
    
    strcpy(p1, "Test string in 32 bytes");
    printf("Allocated 32 bytes at: %p, data: %s\n", p1, p1);
    
    p1 = realloc(p1, 64); // Espandi a 64 byte
    if (!p1) { printf("realloc failed\n"); return 1; }
    
    printf("Reallocated to 64 bytes at: %p, data: %s\n", p1, p1);

    // Scenario 2: Riallocare riducendo la memoria (shrink)
    p1 = realloc(p1, 16); // Riduci a 16 byte
    if (!p1) { printf("realloc failed\n"); return 1; }
    
    printf("Reallocated to 16 bytes at: %p, data: %s\n", p1, p1);

    // Scenario 3: Riallocare con puntatore NULL (equivalente a malloc)
    char *p2 = realloc(NULL, 40); // Allocazione come malloc
    if (!p2) { printf("realloc failed\n"); return 1; }
    
    strcpy(p2, "This is a new allocation");
    printf("Reallocated from NULL to 40 bytes at: %p, data: %s\n", p2, p2);

    // Scenario 4: Riallocare con size 0 (equivalente a free)
    p2 = realloc(p2, 0); // Libera la memoria
    if (p2 == NULL) {
        printf("Reallocated with 0 bytes (freed), p2 is now NULL\n");
    } else {
        printf("Error: p2 should be NULL after realloc with size 0\n");
    }

    // Scenario 5: Riallocare blocco non contiguo
    char *p3 = malloc(50); // Allocazione iniziale di 50 byte
    if (!p3) { printf("malloc failed\n"); return 1; }
    
    strcpy(p3, "This is a 50-byte allocation");
    printf("Allocated 50 bytes at: %p, data: %s\n", p3, p3);

    // Alloca un secondo blocco che dovrebbe essere adiacente al primo
    char *p4 = malloc(50); // Un altro blocco di 50 byte
    if (!p4) { printf("malloc failed\n"); return 1; }
    
    printf("Allocated another 50 bytes at: %p\n", p4);

    // Rialloca il primo blocco a 100 byte (potrebbe richiedere nuovo blocco)
    p3 = realloc(p3, 100);
    if (!p3) { printf("realloc failed\n"); return 1; }
    
    printf("Reallocated p3 to 100 bytes at: %p, data: %s\n", p3, p3);

    // Libera tutti i blocchi
    free(p1);
    free(p3);
    free(p4);

    return 0;
}
