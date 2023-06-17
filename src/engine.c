// Local headers
#include <engine.h>

void render(char *data, int fSize) { // TODO: When procedures become more complex parse operations into AST
    TokenData *tokenTail = run_pipeline(data, fSize);
    if(tokenTail == NULL) {
        fprintf(stderr, "ERORR: Memory allocation failure\n");
        exit(1);
    }
    TokenData *activeToken = tokenTail;

    while(activeToken != NULL) {
        activeToken->type = '{';
        switch(activeToken->type)
        {
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
        activeToken = activeToken->prevSet;
    }
    free_tokens(tokenTail);
    tokenTail = NULL;
    activeToken = NULL;
}

