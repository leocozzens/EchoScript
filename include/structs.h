#ifndef STRUCTS_H
#define STRUCTS_H

#define TOKEN_NUM 10
#define TOKEN_SIZE 20

#include <stdio.h>

typedef struct TokenData {
    char type;
    char **tokenSet; // Set array of args divided by spaces
    size_t filePositon; // Store positions of blocks
    int tokenIndex;
    size_t lastIndex;
    int resizesX;
    int resizesY;
    struct TokenData *nextSet;
} TokenData;

typedef struct {
    FILE *pF;
    char *buffer;
    size_t fSize;
} FileData;

#endif