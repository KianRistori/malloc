#include "malloc.h"

int main() {
	void *p1 = malloc(12);
	void *p2 = malloc(256);

	void *p3 = malloc(30000);

	free(p2);
	free(p3);

	return 0;
}

