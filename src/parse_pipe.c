// Standard C libraries
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Local headers
#include <structs.h>
#include <utils.h>

#define TOKEN_NUM 10
#define TOKEN_SIZE 20

TokenData *lexFile(char *buffer, int fSize) {
    int i = 0;
    _Bool looking = 1;
    int tokenIndex = 0;
    int tokenPos = 0;

    TokenData *retToken = malloc(sizeof(TokenData)); // TODO: Relegate declaration of token struct in a func
    if(retToken == NULL) return NULL;

    retToken->tokenSet = dynamic_grid(TOKEN_NUM, TOKEN_SIZE);
    if(retToken->tokenSet == NULL) {
        free(retToken);
        return NULL;
    }
    
    retToken->resizesX = 1;
    retToken->resizesY = 1;
    retToken->tokenCount = 1;

    while(i < fSize && looking) {
        if(buffer[i] == '{' && buffer[i + 1] == '{') { // TODO: refactor to nested switch statement, and buffer for efficiency
            retToken->filePositon = i;
            i += 2;
            while(isspace(buffer[i])) i++;

            while(i < fSize && !(buffer[i] == '}' && buffer[i + 1] == '}')) {
                retToken->tokenSet[tokenIndex][tokenPos++] = buffer[i];
                i++;
                if(tokenPos >= (retToken->resizesX * TOKEN_SIZE)) {
                    retToken->tokenSet = grid_add_columns(retToken->tokenSet, TOKEN_NUM * retToken->resizesY, TOKEN_SIZE * ++retToken->resizesX);
                    if(retToken->tokenSet[tokenIndex] == NULL) {
                        free(retToken->tokenSet[tokenIndex]);
                        free(retToken);
                        return NULL;
                    }
                }
                if(isspace(buffer[i]) && retToken->filePositon + 4 != i) {
                    retToken->tokenSet[tokenIndex++][tokenPos] = '\0';
                    retToken->tokenCount++;
                    tokenPos = 0;
                    while(isspace(buffer[i])) i++;
                }
                if(tokenIndex >= (retToken->resizesY * TOKEN_NUM)) {
                    retToken->tokenSet = grid_add_rows(retToken->tokenSet, TOKEN_NUM * retToken->resizesY++, TOKEN_SIZE * retToken->resizesX, TOKEN_NUM);
                    if(retToken->tokenSet == NULL) {
                        free(retToken->tokenSet);
                        free(retToken);
                        return NULL;
                    }
                }
            }
            looking = 0;
            retToken->tokenSet[tokenIndex][tokenPos] = '\0';
            if(strlen(retToken->tokenSet[tokenIndex]) == 0 && tokenIndex > 0) retToken->tokenCount--;
        }
        if(looking) i++;
    }
    if(!looking) {
        retToken->type = '{';
    }
    else { // If no tokens were found free everything
        grid_free(retToken->tokenSet, TOKEN_NUM * retToken->resizesY);
        free(retToken);
        retToken = NULL;
    }
    return retToken;
}