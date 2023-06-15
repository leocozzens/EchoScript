// C Standard Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Local headers
#include <file_interface.h>
#include <utils.h>
#include <parse_pipe.h>

#define NAME_SIZE 255
#define END_LINE '\n'

int main(void) {
    printf("\nPlease enter the file you'd like to translate: ");
    char fileName[NAME_SIZE];
    fgets(fileName, sizeof(fileName), stdin);
    char *endLine = strchr(fileName, END_LINE);
    if(endLine != NULL) *endLine = '\0';

    FileData *input = getFile(fileName);

    TokenData *output = runParser(input->buffer, input->fSize);
    if(output == NULL) {
        fprintf(stderr, "ERORR: Memory allocation failure\n");
        exit(1);
    }
    while(output->nextSet != NULL) {
        for(int i = 0; i < output->tokenIndex + 1; i++)
            printf("And the value is:-%s, position %d, at index %d\n", output->tokenSet[i], output->filePositon, i);
        output = output->nextSet;
        printf("\n");
    }
    free_tokens(output);
    output = NULL;

    closeFile(&input);
    return 0;
}