#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define OPEN_MAX 20
#define PERMS 0666

typedef struct _iobuf {
    int fd;         /* file descriptor */
    int cnt;        /* characters left */
    char *ptr;      /* next character position */
    char *base;     /* buffer location */

    int readable;
    int writable;
    int unbuf;
    int eof;
    int error;
} FILE2;

FILE2 _iob[OPEN_MAX];

FILE2 *fopen2(char *name, char *mode)
{
    int fd;
    FILE2 *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (fp->readable == 0 && fp->writable == 0)
            break;

    if (fp >= _iob + OPEN_MAX)
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY);

    if (fd == -1)
        return NULL;

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->ptr = NULL;

    fp->readable = (*mode == 'r');
    fp->writable = (*mode != 'r');
    fp->unbuf = 0;
    fp->eof = 0;
    fp->error = 0;

    return fp;
}

int _fillbuf2(FILE2 *fp)
{
    int bufsize;

    if (!fp->readable || fp->eof || fp->error)
        return EOF;

    bufsize = fp->unbuf ? 1 : BUFSIZ;

    if (fp->base == NULL) {
        fp->base = (char *) malloc(bufsize);
        if (fp->base == NULL) {
            fp->error = 1;
            return EOF;
        }
    }

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if (fp->cnt <= 0) {
        if (fp->cnt == 0)
            fp->eof = 1;
        else
            fp->error = 1;

        fp->cnt = 0;
        return EOF;
    }

    fp->cnt--;
    return (unsigned char) *fp->ptr++;
}

int getc2(FILE2 *fp)
{
    return (--fp->cnt >= 0)? (unsigned char) *fp->ptr++ : _fillbuf2(fp);
}

int main(int argc, char *argv[])
{
    FILE2 *fp;
    int c;

    if (argc < 2) {
        printf("FILE NAME NOT GIVEN");
        return 1;
    }

    fp = fopen2(argv[1], "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while ((c = getc2(fp)) != EOF)
        putchar(c);

    return 0;
}
