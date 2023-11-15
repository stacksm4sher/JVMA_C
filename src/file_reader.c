#include <stdio.h>
#include <malloc.h>
#include <string.h>

char *read_raw_bytecode_from_file(char *filename) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        return NULL;
    }

    unsigned long long bytes_read = 0;
    char *bytecode = (char *) malloc(1024 * sizeof(char *));
    char *buffer = (char *) malloc(1024 * sizeof(char *));
    while (!feof(file)) {
        unsigned long long bytes_read_n = fread(buffer, sizeof(char), 1024, file);
        memcpy(bytecode + bytes_read, buffer, bytes_read_n);
        bytes_read += bytes_read_n;
        bytecode = (char *) realloc(
                (void *) bytecode,
                ((bytes_read % 1024 == 0) * bytes_read * 2)
                + ((bytes_read % 1024 != 0) * bytes_read)
        );
    }

    fclose(file);
    free(buffer);

    return bytecode;
}
