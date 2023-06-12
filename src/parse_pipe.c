#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// Local headers
#include <utils.h>

#define TOKEN_NUM 10
#define TOKEN_SIZE 20

typedef struct {
    char type;
    char **tokenSet; // Set array of args divided by spaces
    int *filePositon; // Store positions of blocks,TODO: look into making this variable size_t
} Token;

Token *lexFile(char *buffer, int fSize) {
    int i = 0;
    _Bool looking = 1;
    int tokenIndex = 0;
    int tokenPos = 0;
    int resizesX = 1;
    int resizesY = 1;

    Token *retToken = malloc(sizeof(Token)); // TODO: Relegate declaration of token struct in a func
    if(retToken == NULL) return NULL;

    retToken->filePositon = malloc(TOKEN_NUM * sizeof(int));
    if(retToken->filePositon == NULL) {
        free(retToken);
        return NULL;
    }

    retToken->tokenSet = dynamic_grid(TOKEN_NUM, TOKEN_SIZE);
    if(retToken->tokenSet == NULL) {
        free(retToken->filePositon);
        free(retToken);
        return NULL;
    }
    while(i < fSize && looking) {
        if(buffer[i] == '{' && buffer[i + 1] == '{') { // TODO: refactor to nested switch statement, and buffer for efficiency
            retToken->filePositon[tokenIndex] = i;
            i += 2;
            while(i < fSize && !(buffer[i] == '}' && buffer[i + 1] == '}')) {
                retToken->tokenSet[tokenIndex][tokenPos++] = buffer[i];
                i++;
                if(tokenPos >= (resizesX * TOKEN_SIZE)) {
                    retToken->tokenSet[tokenIndex] = realloc(retToken->tokenSet[tokenIndex], TOKEN_SIZE * ++resizesX);
                    if(retToken->tokenSet[tokenIndex] == NULL) {
                        free(retToken->tokenSet[tokenIndex]);
                        return NULL;
                    }
                }
            }
            looking = 0;
            retToken->tokenSet[tokenIndex][tokenPos] = '\0';
        }
        if(looking) i++;
    }
    if(!looking) {
        retToken->type = '{';
    }
    else { // If no tokens were found free everything
        grid_free(retToken->tokenSet, TOKEN_NUM * resizesY);
        free(retToken->filePositon);
        free(retToken);
        retToken = NULL;
    }
    return retToken;
}