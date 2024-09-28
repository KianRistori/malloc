#include <stdlib.h>
#include <stdio.h>

#define M (1024 * 1024)

int main(int argc, char const *argv[])
{
    printf("Hello, World!\n");
    char *addr1;
    
    addr1 = (char*)malloc(128*M);
    addr1[127*M] = 42;
    return 0;
}
