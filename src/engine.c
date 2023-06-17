// Local headers
#include <engine.h>

FileData *render(FileData *inFile) { // TODO: When procedures become more complex parse operations into AST
    TokenData *tokenHead = run_pipeline(inFile->buffer, inFile->fSize);
    if(tokenHead == NULL) {
        fprintf(stderr, "ERORR: Memory allocation failure\n");
        exit(1);
    }
    TokenData *activeToken = tokenHead;

    if(activeToken->type == '0') {
        fprintf(stderr, "ERROR: No command structure present in file\n");
        exit(1);
    }

    char *outBuffer = malloc(inFile->fSize + 1);
    transform_tokens(inFile->buffer, inFile->fSize, outBuffer, tokenHead);

    while(activeToken != NULL) {
        activeToken->type = '{';
        switch(activeToken->type) {
            case '0':
                fprintf(stderr, "ERROR: No command structure present in file\n");
                exit(1);
                break;
            case '{':
                for(int i = 0; i < activeToken->tokenIndex + 1; i++) {
                    printf("The value is:-%s, position %d, at index %d\n", activeToken->tokenSet[i], activeToken->filePositon, i);
                }
                break;

            default:
                fprintf(stderr, "ERROR: No expression type\n");
                exit(1);
                break;
        }
        printf("\n");
        activeToken = activeToken->nextSet;
    }
    free_tokens(tokenHead);
    tokenHead = NULL;
    activeToken = NULL;
    FileData *retData = malloc(sizeof(FileData));
    retData->buffer = outBuffer;
    retData->fSize = inFile->fSize + 1;
    return retData;
}

void transform_tokens(char *inBuff, int buffSize, char *outBuff, TokenData *tokenHead) {
    TokenData *activeToken = tokenHead;
    int newIter = 0;
    int oldIter = 0;
    while(oldIter < buffSize) {
        if(oldIter == activeToken->filePositon) {
            printf("\nFile position: %d\nlastIndex = %d\noldIter: %d\n", activeToken->filePositon, activeToken->lastIndex, oldIter);
            oldIter += activeToken->lastIndex - activeToken->filePositon;
            if(activeToken->nextSet != NULL) activeToken = activeToken->nextSet;
        }
        outBuff[newIter] = inBuff[oldIter];
        newIter++;
        oldIter++;
    }
    outBuff[newIter] = '\0';
}