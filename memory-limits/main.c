#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "error: missing <num_bytes> argument\n");
        return 1;
    }
    uintmax_t num_bytes = strtoumax(argv[1], NULL, 10);
    if (num_bytes == UINTMAX_MAX && errno == ERANGE) {
        fprintf(stderr, "error <num_bytes> argument too large\n");
        return 1;
    }

    uint8_t *bytes = malloc(num_bytes * sizeof(uint8_t));
    if (bytes == NULL) {
        fprintf(stderr, "failed to allocate <num_bytes>\n");
        return 1;
    }
    printf("successfully allocated %ld bytes\n", num_bytes);

    // Force the allocated memory into RAM and prevent it from being paged
    mlock(bytes, num_bytes);
    printf("successfully forced allocated memory into RAM\n");

    pid_t pid = getpid();
    printf("pid: %d\n\n", pid);
    printf("press any key to exit");
    getchar();

    return 0;
}

