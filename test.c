#include <stdio.h>
#include "malloc.h"

int main() {
	// Effettua alcune allocazioni
	void *p1 = malloc(32);
	printf("Allocated 32 bytes at: %p\n", p1);

	void *p2 = malloc(128);
	printf("Allocated 128 bytes at: %p\n", p2);

	void *p3 = malloc(256);
	printf("Allocated 256 bytes at: %p\n", p3);

	// Ora puoi anche visualizzare la differenza tra gli indirizzi
	printf("Address difference between p1 and p2: %ld bytes\n", (char *)p2 - (char *)p1);
	printf("Address difference between p2 and p3: %ld bytes\n", (char *)p3 - (char *)p2);

	// Libera la memoria
	free(p1);
	free(p2);
	free(p3);

	p1 = malloc(32);
	printf("Allocated 32 bytes at: %p\n", p1);
	p2 = malloc(32);
	printf("Allocated 32 bytes at: %p\n", p2);
	
	free(p1);
	free(p2);	
	return 0;
}

