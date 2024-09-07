#include "malloc.h"

int main() {
	void *p1 = malloc(12);
	void *p2 = malloc(256);
	void *pRealloc = realloc(p2, 261);

	void *p3 = malloc(1024 * 1024);

	free(p1);
	free(p3);
	free(pRealloc);

	return 0;
}

