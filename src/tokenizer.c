// Local headers
#include <tokenizer.h>

TokenData *tokenize_file(char *buffer, int fSize) {
    TokenData *activeToken = NULL;

    int i = 0;
    _Bool found = 0;
    int tokenPos = 0;

    while(i < fSize) {
        if(buffer[i] == '{') {
            char operator = buffer[i + 1];
            switch(operator) {
                case '{':
                {
                    reserve_token(&activeToken);
                    if(activeToken == NULL) return NULL;
                    found = 1;
                    activeToken->filePositon = i;
                    activeToken->type = operator;
                    i += 2;
                    while(isspace(buffer[i])) i++;
                    if(extract_tokens(buffer, fSize, &i, activeToken, &tokenPos, '}')) {
                        free_tokens(activeToken);
                        return NULL;
                    }

                    break;
                }
                default:
                    break;
            }
        }
        i++;
    }
    if(!found) // If no tokens set type to none
        activeToken->type = '0';
    return activeToken;
}

_Bool extract_tokens(char *buffer, int fSize, int *index, TokenData *activeToken, int *tokenPos, char closingOperator) {
    while(*index < fSize) {
        if(buffer[*index] == closingOperator && buffer[*index + 1] == '}') {
            (*index)++; // If end of command structure at EOF is causing out of bounds look here
            break;
        }
        activeToken->tokenSet[activeToken->tokenIndex][(*tokenPos)++] = buffer[(*index)++];
    
        if(*tokenPos >= (activeToken->resizesX * TOKEN_SIZE)) {
            activeToken->tokenSet = grid_add_columns(activeToken->tokenSet, TOKEN_NUM * activeToken->resizesY, TOKEN_SIZE * ++activeToken->resizesX);
            if(activeToken->tokenSet[activeToken->tokenIndex] == NULL) return 1;
        }

        if(isspace(buffer[*index])) {
            while(isspace(buffer[*index])) (*index)++;
            if(buffer[*index] == closingOperator && buffer[*index + 1] == '}') break;
            activeToken->tokenSet[activeToken->tokenIndex++][*tokenPos] = '\0';
            *tokenPos = 0;
        }

        if(activeToken->tokenIndex >= (activeToken->resizesY * TOKEN_NUM)) {
            activeToken->tokenSet = grid_add_rows(activeToken->tokenSet, TOKEN_NUM * activeToken->resizesY++, TOKEN_SIZE * activeToken->resizesX, TOKEN_NUM);
            if(activeToken->tokenSet == NULL) return 1;
        }
    }
    activeToken->tokenSet[activeToken->tokenIndex][*tokenPos] = '\0'; // If the first character is \0 it means the command structure is empty and should be removed
    *tokenPos = 0;
    return 0;
}

void reserve_token(TokenData **activeToken) {
    if(*activeToken == NULL) {
        *activeToken = malloc(sizeof(TokenData));
        (*activeToken)->filePositon = 333;
        (*activeToken)->prevSet = NULL;
    }
    else {
        TokenData *tmp = malloc(sizeof(TokenData));
        tmp->prevSet = *activeToken;
        *activeToken = tmp;
    }

    if((*activeToken) == NULL) {
        *activeToken = NULL;
        return;
    }
    (*activeToken)->tokenSet = dynamic_grid(TOKEN_NUM, TOKEN_SIZE);
    if((*activeToken)->tokenSet == NULL) {
        free(*activeToken);
        *activeToken = NULL;
        return;
    }

    (*activeToken)->resizesX = 1;
    (*activeToken)->resizesY = 1;
    (*activeToken)->tokenIndex = 0;
}

void free_tokens(TokenData *lastToken) {
    if(lastToken == NULL) return;
    TokenData *tmpToken = lastToken;
    TokenData *prevToken;
    while(tmpToken != NULL) {
        prevToken = tmpToken->prevSet;
        grid_free(tmpToken->tokenSet, tmpToken->tokenIndex + 1);
        free(tmpToken);
        tmpToken = prevToken;
    }
}