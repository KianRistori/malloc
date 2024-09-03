#include <stdio.h>
#include "malloc.h"

int main()
{
	char* str = "Hello";
	int len = ft_strlen(str);
	printf("len: %d\n", len);
	return 0;
}
