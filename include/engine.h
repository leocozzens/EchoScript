#ifndef RENDER_H
#define RENDER_H

// C standard headers
#include <stdio.h>

// Local headers
#include <parser.h>

FileData *render(FileData *inFile);
void transform_tokens(char *inBuff, int buffSize, char *outBuff, TokenData *tokenHead);

#endif