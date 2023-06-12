#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    char type;
    char *variable; // Set array of args divided by spaces
} Token;

Token *lexFile(const char *buffer, int fSize) {
    int i = 0;
    _Bool looking = 1;
    int tokenPos = 0;
    char token[20];
    Token *retToken = malloc(sizeof(Token));
    while(i < fSize && looking) {
        if(buffer[i] == '{' && buffer[i + 1] == '{') { // TODO: refactor to nested switch statement, and buffer for efficiency 
            i += 2;
            while(i < fSize && !(buffer[i] == '}' && buffer[i + 1] == '}')) {
                token[tokenPos++] = buffer[i];
                i++;
            }
            looking = 0;
            token[tokenPos] = '\0';
        }
        if(looking) i++;
    }
    if(!looking) { // Return array of tokens
        retToken->type = '{';
        retToken->variable = malloc(strlen(token) + 1);
        strcpy(retToken->variable, token);
    }
    else {
        free(retToken);
        retToken = NULL;
    }
    return retToken;
}