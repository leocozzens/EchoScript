#ifndef PARSE_PIPE_H
#define PARSE_PIPE_H

#define TOKEN_NUM 10
#define TOKEN_SIZE 20

typedef struct {
    char type;
    char **tokenSet; // Set array of args divided by spaces
    int *filePositon; // Store positions of blocks
} Token;

Token *lexFile(const char *buffer, int fSize);

#endif