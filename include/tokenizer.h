#ifndef TOKENIZER_H
#define TOKENIZER_H

// Standard C libraries
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Local headers
#include <structs.h>
#include <utils.h>

TokenData *tokenize_file(char *buffer, int fSize);
_Bool extract_tokens(char *buffer, int fSize, int *index, TokenData *activeToken, int *tokenPos, char closingOperator);
void reserve_token(TokenData **activeToken);
void free_tokens(TokenData *firstToken);

#endif