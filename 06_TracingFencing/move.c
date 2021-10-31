#include <stdio.h>
#include <stdlib.h>

enum {
    OK,
    ARGS_ERROR,
    IN_OPEN_ERROR,
    IN_SIZE_ERROR,
    IN_MEMORY_ERROR,
    IN_READ_ERROR,
    IN_CLOSE_ERROR,
    OUT_OPEN_ERROR,
    OUT_WRITE_ERROR,
    OUT_REMOVE_ERROR,
    OUT_CLOSE_ERROR,
    IN_REMOVE_ERROR
};

int main(int argc, char *argv[]) {
    if (argc != 3) return ARGS_ERROR;

    FILE *in;
    long length;
    char *buffer;
    if ((in = fopen(argv[1], "r")) == NULL) {
        return IN_OPEN_ERROR;
    }
    if (fseek(in, 0, SEEK_END) || (length = ftell(in)) == -1L || fseek(in, 0, SEEK_SET)) {
        if (fclose(in)) return IN_CLOSE_ERROR;
        return IN_SIZE_ERROR;
    }
    if (!(buffer = malloc(length))) {
        if (fclose(in)) return IN_CLOSE_ERROR;
        return IN_MEMORY_ERROR;
    }
    if (fread(buffer, 1, length, in) != length) {
        free(buffer);
        if (fclose(in)) return IN_CLOSE_ERROR;
        return IN_READ_ERROR;
    }
    if (fclose(in)) {
        free(buffer);
        return IN_CLOSE_ERROR;
    }

    FILE *out;
    if ((out = fopen(argv[2], "w")) == NULL) {
        free(buffer);
        return OUT_OPEN_ERROR;
    }
    if (fputs(buffer, out) == EOF) {
        free(buffer);
        if (fclose(out)) return OUT_CLOSE_ERROR;
        if (remove(argv[2])) return OUT_REMOVE_ERROR;
        return OUT_WRITE_ERROR;
    }
    free(buffer);
    if (fclose(out)) return OUT_CLOSE_ERROR;
    if (remove(argv[1])) return IN_REMOVE_ERROR;
}