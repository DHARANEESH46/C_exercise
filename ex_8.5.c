/*Modify the fsize program to print the other information contained in the inode
entry.*/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

#ifndef S_IFMT
#define S_IFMT  0160000
#endif
#ifndef S_IFDIR
#define S_IFDIR 0040000
#endif
#ifndef S_IFREG
#define S_IFREG 0100000
#endif

#define MAX_PATH 1024
#define DIRSIZ 14

typedef struct {
    long ino;
    char name[DIRSIZ+1];
} dirent;

void fsize(char *name);
void dirwalk(char *dir, void (*fcn)(char *));

int main(int argc, char **argv)
{
    if (argc == 1)
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);

    return 0;
}

void fsize(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }

    printf("File: %s\n", name);
    printf("Size: %ld bytes\n", (long)stbuf.st_size);
    printf("Inode: %ld\n", (long)stbuf.st_ino);
    printf("Links: %ld\n", (long)stbuf.st_nlink);
    printf("UID: %d\n", stbuf.st_uid);
    printf("GID: %d\n", stbuf.st_gid);
    printf("Access time: %ld\n", (long)stbuf.st_atime);
    printf("Modify time: %ld\n", (long)stbuf.st_mtime);
    printf("Change time: %ld\n", (long)stbuf.st_ctime);

    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        printf("Type: Directory\n");
    else if ((stbuf.st_mode & S_IFMT) == S_IFREG)
        printf("Type: Regular file\n");
    else
        printf("Type: Other\n");

    printf("-----------------------------\n");

    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, fsize);
}

void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[MAX_PATH];
    dirent *dp;
    DIR *dfd;
    struct dirent *entry;

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }

    while ((entry = readdir(dfd)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0
        || strcmp(entry->d_name, "..") == 0)
            continue;

        if (strlen(dir) + strlen(entry->d_name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s %s too long\n",
                    dir, entry->d_name);
        else {
            sprintf(name, "%s/%s", dir, entry->d_name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}
