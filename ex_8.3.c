/*Design and write _flushbuf, fflush, and fclose.*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define OPEN_MAX 20
#define PERMS 0666
#define EOF (-1)

typedef struct _io_buf {
    int fd;
    int cnt;
    char *ptr;
    char *base;

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
        if (!fp->readable && !fp->writable)
            break;

    if (fp >= _iob + OPEN_MAX)
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else
        fd = open(name, O_WRONLY);

    if (fd == -1)
        return NULL;

    fp->fd = fd;
    fp->base = malloc(BUFSIZ);
    fp->ptr = fp->base;
    fp->cnt = BUFSIZ;
    fp->writable = 1;

    return fp;
}

int _flushbuf2(FILE2 *fp)
{
    int n = fp->ptr - fp->base;

    if (n > 0)
        write(fp->fd, fp->base, n);

    fp->ptr = fp->base;
    fp->cnt = BUFSIZ;
    return 0;
}

int fflush2(FILE2 *fp)
{
    return _flushbuf2(fp);
}

int fclose2(FILE2 *fp)
{
    _flushbuf2(fp);
    free(fp->base);
    close(fp->fd);
    fp->writable = 0;
    return 0;
}

int main(void)
{
    FILE2 *fp;
    char *msg = "Hello Iam Dharaneesh V\n";

    fp = fopen2("output.txt", "w");

    for (int i = 0; msg[i]; i++) {
        *fp->ptr++ = msg[i];
        if (--fp->cnt == 0)
            _flushbuf2(fp);
    }

    fclose2(fp);
    printf("Written successfully\n");
    return 0;
}
