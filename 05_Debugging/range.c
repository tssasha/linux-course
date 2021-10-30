#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int start = 0, stop, step = 1;
    if (argc == 1) {
        printf("help\n");
        return 0;
    }
    if (argc == 2) {
        sscanf(argv[1], "%d", &stop);
    }
    if (argc >= 3) {
        sscanf(argv[1], "%d", &start);
        sscanf(argv[2], "%d", &stop);
    }
    if (argc == 4) {
        sscanf(argv[3], "%d", &step);
    }
    for (int i = start; (step > 0 && i < stop) || (step < 0 && i > stop); i += step) {
        printf("%d\n", i);
    }
    return 0;
}