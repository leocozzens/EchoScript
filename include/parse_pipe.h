#ifndef PARSE_PIPE_H
#define PARSE_PIPE_H

// Standard C libraries
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Local headers
#include <structs.h>
#include <utils.h>

TokenData *lexFile(char *buffer, int fSize);
void trimTokens(TokenData *firstToken);

#endif