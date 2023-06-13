#ifndef STRUCTS_H
#define STRUCTS_H

#define TOKEN_NUM 10
#define TOKEN_SIZE 20

typedef struct TokenData {
    char type;
    char **tokenSet; // Set array of args divided by spaces
    int filePositon; // Store positions of blocks,TODO: look into making this variable size_t
    int tokenCount;
    int resizesX;
    int resizesY;
    struct TokenData *nextSet;
} TokenData;

#endif