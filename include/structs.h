#ifndef STRUCTS_H
#define STRUCTS_H

#define TOKEN_NUM 10
#define TOKEN_SIZE 20

#include <stdio.h>

typedef struct TokenData {
    char type;
    char **tokenSet; // Set array of args divided by spaces
    int filePositon; // Store positions of blocks,TODO: look into making this variable size_t
    int tokenIndex;
    int lastIndex;
    int resizesX;
    int resizesY;
    struct TokenData *nextSet;
} TokenData;

typedef struct {
    FILE *pF;
    char *buffer;
    int fSize;
} FileData;

#endif