#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main() {
    char buffer[4096];
    size_t totalSize = 0;
    struct stat fileStat;

    while (scanf("%4095s", buffer) == 1) {
       

        if (stat(buffer, &fileStat) == 0) {
            if (S_ISREG(fileStat.st_mode)) {
                totalSize += fileStat.st_size;
            }
        } else {
           fprintf(stderr, "Failed to get file info: %s: errno = %d\n", buffer, errno);
        }
    }

    printf("%zu\n", totalSize);

    return 0;
}