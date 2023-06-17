// Local headers
#include <engine.h>

void render(char *data, int fSize) { // TODO: When procedures become more complex parse operations into AST
    TokenData *tokenHead = run_pipeline(data, fSize);
    if(tokenHead == NULL) {
        fprintf(stderr, "ERORR: Memory allocation failure\n");
        exit(1);
    }
    TokenData *activeToken = tokenHead;
    
    if(activeToken->type == '0') {
        fprintf(stderr, "ERROR: No command structure present in file\n");
        exit(1);
    }

    char *outBuffer = malloc(strlen(data) + 1);
    int newIter = 0;
    int oldIter = 0;
    while(oldIter < fSize) {
        if(oldIter == activeToken->filePositon) {
            printf("\nFile position: %d\nlastIndex = %d\noldIter: %d\n", activeToken->filePositon, activeToken->lastIndex, oldIter);
            oldIter += activeToken->lastIndex - activeToken->filePositon;
            if(activeToken->nextSet != NULL) activeToken = activeToken->nextSet;
        }
        outBuffer[newIter] = data[oldIter];
        newIter++;
        oldIter++;
    }
    outBuffer[newIter] = '\0';
    printf("%s%%\n", outBuffer);
    activeToken = tokenHead;
    while(activeToken != NULL) {
        activeToken->type = '{';
        switch(activeToken->type) {
            case '0':
                fprintf(stderr, "ERROR: No command structure present in file\n");
                exit(1);
                break;
            case '{':
                for(int i = 0; i < activeToken->tokenIndex + 1; i++) {
                    printf("And the value is:-%s, position %d, at index %d\n", activeToken->tokenSet[i], activeToken->filePositon, i);
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
}
