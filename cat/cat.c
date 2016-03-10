#include <unistd.h>

const ssize_t BUF_SIZE = 1024;

int main(int argv, char ** argc) {
    char buffer[BUF_SIZE];
    ssize_t size = 0;
    while ((size = read(STDIN_FILENO, buffer, BUF_SIZE)) > 0) {
        write(STDOUT_FILENO, buffer, size);
    }
    if (size < 0) {
        puts("Some error occured\n");
        return size;
    }
    return 0;
}
