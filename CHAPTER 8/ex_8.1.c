/*Rewrite the program cat from Chapter 7 using read, write, open, and close
instead of their standard library equivalents. Perform experiments to determine the relative
speeds of the two versions.*/

#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZ 1024

void copy(int from, int to)
{
    char buf[BUF_SIZ];
    int n;

    while ((n = read(from, buf, BUF_SIZ)) > 0)
        write(to, buf, n);
}

void error(char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}


int main(int argc, char *argv[])
{
    int fd;
    char *prog = argv[0];

    if (argc == 1) {
        copy(0, 1);
    }
    else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY,0)) == -1) {
                error("%s: can't open %s", prog, *argv);
            }
            copy(fd, 1);
            close(fd);
        }
    }
    return 0;
}
