#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "error: missing <num_bytes> argument\n");
        return 1;
    }
    uintmax_t num_bytes = strtoumax(argv[1], NULL, 10);
    if (num_bytes == UINTMAX_MAX && errno == ERANGE) {
        fprintf(stderr, "error: <num_bytes> argument too large\n");
        return 1;
    }
    uint8_t *bytes = malloc(num_bytes * sizeof(uint8_t));
    printf("successfully allocated %ld bytes\n", num_bytes);
    return 0;
}
