#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
const ssize_t BUF_SIZE = 1024;

void cat(int from, int to) {
    char buffer[BUF_SIZE];
    ssize_t size = 0;
    while ((size = read(from, buffer, BUF_SIZE)) > 0 || errno == EINTR) {
        ssize_t count = 0;
        while (count < size) {
            ssize_t val = write(to, buffer + count, size - count);
            if (val < 0) {
                if (errno == EINTR) {
                    continue;
                }
                puts("Can't write");
                return;
            }
            count += val;
        }
    }
    if (size < 0) {
        puts("Can't read");
    }
    return;
}

int main(int argc, char ** argv) {
    if (argc == 1) {
        cat(0, 1);
    } else {
        int i = 1;
        for (i = 1; i < argc; i++) {
            size_t from = open(argv[i], O_RDONLY);
            if (from == -1) {
                puts("Can't open file ", argv[i]);
                continue;
            }
            cat(from, 1);
            close(from);
        } 
    }
    return 0;
}
