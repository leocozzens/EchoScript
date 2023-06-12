// C Standard Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Local headers
#include <parse_pipe.h>
#include <utils.h>

#define NAME_SIZE 255

int main() {
    printf("\nPlease enter the file you'd like to translate: ");
    char fileName[NAME_SIZE];
    fgets(fileName, sizeof(fileName), stdin);
    fileName[strlen(fileName) - 1] = '\0';

    // Set file pointer
    FILE *pF = NULL;
    pF = fopen(fileName, "r");
    if(pF == NULL) {
        printf("Failed to open file...\n");
        return 1;
    }

    fseek(pF, 0, SEEK_END); // Sets the file position indicator to the last element in the contiguous block
    int fSize = ftell(pF); // ftell returns the offset of the position indicator from the initial address
    rewind(pF); // Returns the position pointer to base

    char *buffer = malloc(fSize + 1); // +1 for null terminator
    if(buffer == NULL) {
        fclose(pF);
        return 1;
    }

    // Read the file contents into the buffer
    fread(buffer, sizeof(char), fSize, pF);
    buffer[fSize + 1] = '\0';

    //printf("file contents:\n%s\n", buffer);

    TokenData *output = lexFile(buffer, fSize);
    if(output == NULL) return 0;
    for(int i = 0; i < output->tokenCount; i++)
        printf("And the value is:-%s, position %d, at index %d\n", output->tokenSet[i], output->filePositon, i + 1);

    grid_free(output->tokenSet, TOKEN_NUM * output->resizesY); // TODO: Struct free function
    free(output);

    fclose(pF);
    return 0;
}