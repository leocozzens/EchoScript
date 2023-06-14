#ifndef FILE_INTERFACE_H
#define FILE_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct {
    FILE *pF;
    char *buffer;
    int fSize;
} FileData;


FileData *getFile(char *fileName);

#endif