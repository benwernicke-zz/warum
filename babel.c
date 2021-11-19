#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char* WORDS[] = { "Ben", "essen", "hallo", "moin" };
#define N_WORDS 10

int main()
{
    size_t seed;
    printf("The Book you shall get be named: ");
    scanf("%ld", &seed);
    srand(seed);
    printf("\n");
    for (int i = 0; i < N_WORDS; i++)
        printf("%s ", WORDS[(size_t)rand() % 4]);
    printf("\n");
    return 0;
}
