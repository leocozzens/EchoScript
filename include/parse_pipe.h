#ifndef PARSE_PIPE_H
#define PARSE_PIPE_H

typedef struct {
    char type;
    char *args;
} Token;

Token *lexFile(const char *buffer, int fSize);

#endif