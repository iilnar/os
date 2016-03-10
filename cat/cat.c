#include <unistd.h>

int main(int argv, char ** argc) {
    char buffer[1024];
    int size = 0;
    while ((size = read(STDIN_FILENO, buffer, 1024)) > 0) {
        write(STDOUT_FILENO, buffer, size);
    }
    if (size < 0) {
        puts("Some error occured\n");
    }
    return 0;
}
