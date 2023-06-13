// Standard C libraries

// Local headers
#include <parse_pipe.h>

#define TOKEN_NUM 10
#define TOKEN_SIZE 20

TokenData *lexFile(char *buffer, int fSize) {
    TokenData *retToken = malloc(sizeof(TokenData)); // TODO: Relegate declaration of token struct in a func
    if(retToken == NULL) return NULL;

    retToken->tokenSet = dynamic_grid(TOKEN_NUM, TOKEN_SIZE);
    if(retToken->tokenSet == NULL) {
        free(retToken);
        return NULL;
    }

    int i = 0;
    _Bool found = 0;
    int tokenIndex = 0;
    int tokenPos = 0;

    TokenData *activeToken = retToken;
    activeToken->nextSet = NULL;
    activeToken->resizesX = 1;
    activeToken->resizesY = 1;
    activeToken->tokenCount = 1;

    while(i < fSize) {
        if(buffer[i] == '{' && buffer[i + 1] == '{') { // TODO: refactor to nested switch statement, and buffer for efficiency
            found = 1;
            activeToken->filePositon = i;
            i += 2;
            while(isspace(buffer[i])) i++;

            while(i < fSize) {
                if(buffer[i] == '}' && buffer[i + 1] == '}') {
                    activeToken->nextSet = malloc(sizeof(TokenData));
                    if(activeToken->nextSet == NULL) return NULL;
                    activeToken = activeToken->nextSet;

                    activeToken->tokenSet = dynamic_grid(TOKEN_NUM, TOKEN_SIZE);
                    if(activeToken->tokenSet == NULL) {
                        free(retToken);
                        return NULL;
                    }

                    activeToken->nextSet = NULL;
                    activeToken->resizesX = 1;
                    activeToken->resizesY = 1;
                    activeToken->tokenCount = 1;
                    tokenIndex = 0;
                    tokenPos = 0;
                    break;
                }
                activeToken->tokenSet[tokenIndex][tokenPos++] = buffer[i];
                i++;
                if(tokenPos >= (activeToken->resizesX * TOKEN_SIZE)) {
                    activeToken->tokenSet = grid_add_columns(activeToken->tokenSet, TOKEN_NUM * activeToken->resizesY, TOKEN_SIZE * ++activeToken->resizesX);
                    if(activeToken->tokenSet[tokenIndex] == NULL) {
                        free(activeToken->tokenSet[tokenIndex]);
                        free(activeToken);
                        return NULL;
                    }
                }
                if(isspace(buffer[i])) {
                    activeToken->tokenSet[tokenIndex++][tokenPos] = '\0';
                    activeToken->tokenCount++;
                    tokenPos = 0;
                    while(isspace(buffer[i])) i++;
                }
                if(tokenIndex >= (activeToken->resizesY * TOKEN_NUM)) {
                    activeToken->tokenSet = grid_add_rows(activeToken->tokenSet, TOKEN_NUM * activeToken->resizesY++, TOKEN_SIZE * activeToken->resizesX, TOKEN_NUM);
                    if(activeToken->tokenSet == NULL) {
                        free(activeToken->tokenSet);
                        free(activeToken);
                        return NULL;
                    }
                }
            }
            activeToken->tokenSet[tokenIndex][tokenPos] = '\0';
        }
        i++;
    }
    if(found) {
        activeToken->type = '{';
        trimTokens(retToken);
        //return linked list
    }
    else { // If no tokens were found free everything
        grid_free(retToken->tokenSet, TOKEN_NUM * retToken->resizesY);
        free(retToken);
        retToken = NULL;
    }
    return retToken;
}

void trimTokens(TokenData *firstToken) {
        TokenData *tmpToken = firstToken;
        while(tmpToken->nextSet != NULL) {
            if(strlen(tmpToken->tokenSet[tmpToken->tokenCount - 1]) == 0 && tmpToken->tokenCount > 1)
                tmpToken->tokenCount--;
            tmpToken = tmpToken->nextSet;
        }
}