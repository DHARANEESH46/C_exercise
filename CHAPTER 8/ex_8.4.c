/*The standard library function : int fseek(FILE *fp, long offset, int origin)
is identical to lseek except that fp is a file pointer instead of a file descriptor and return value
is an int status, not a position. Write fseek. Make sure that your fseek coordinates properly
with the buffering done for the other functions of the library.*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZ 8

typedef struct {
    int fd;
    int cnt;
    char *ptr;
    char *base;

    struct {
        unsigned f_read  : 1;
        unsigned f_write : 1;
    } flag;
} FILE2;

int _fseek(FILE2 *fp, long offset, int origin)
{
    unsigned nc;
    long rc = 0;
   
    if(fp->flag.f_read)
    {
        if(origin == 1)
            offset -= fp->cnt;

        rc = lseek(fp->fd, offset, origin);
        fp->cnt = 0;
    }
    else if(fp->flag.f_write)
    {
        if((nc = fp->ptr - fp->base) > 0)
            if(write(fp->fd, fp->base, nc) != nc)
                rc = -1;

        if(rc != -1)
            rc = lseek(fp->fd, offset, origin);
    }
    return (rc == -1) ? -1 : 0;
}

int main(void)
{
    FILE2 fp;
    char c;

    fp.fd = open("/home/user/Documents/seek.txt", O_RDONLY);
    if (fp.fd == -1) {
        perror("open");
        return 1;
    }

    fp.base = malloc(BUF_SIZ);
    fp.ptr = fp.base;
    fp.cnt = read(fp.fd, fp.base, BUF_SIZ);
    fp.flag.f_read = 1;
    fp.flag.f_write = 0;

    c = *fp.ptr++; fp.cnt--;
    putchar(c);   

    c = *fp.ptr++; fp.cnt--;
    putchar(c);   

    _fseek(&fp, 2, 0);

    fp.cnt = read(fp.fd, fp.base, BUF_SIZ);
    fp.ptr = fp.base;

    c = *fp.ptr++;
    putchar(c);

    putchar('\n');

    close(fp.fd);
    free(fp.base);
    return 0;
}
