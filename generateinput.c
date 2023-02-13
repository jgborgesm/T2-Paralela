#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
    srand(time(NULL));
    long n, i;

    if (argc > 1)
        n = atol(argv[1]);
    else
        scanf("%ld", &n);
    for (i = 0; i < n; i++) {
        printf("%d ", rand() % 10000000 + 1);
    }
    printf("\n");
    return 0;
}
