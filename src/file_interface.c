#include <file_interface.h>

void clear_input(void) {
    int nextCh;
    while((nextCh = fgetc(stdin)) != '\n' && nextCh != EOF);
}

char *get_input(char *request, char *retStr, int buffSize) {
    printf("%s", request);
    char input[buffSize];
    if(!fgets(input, buffSize, stdin)) exit(0);
    char *endLine = strchr(input, '\n');
    if(endLine != NULL) *endLine = '\0';
    else clear_input();
    strcpy(retStr, input);
}

FileData *get_file(char *fileName) {
    FileData *retData = malloc(sizeof(FileData));
    retData->pF = fopen(fileName, "r");
    if(retData->pF == NULL) { // TODO: Check file type and return an error if it is not a text file
        perror("ERROR");
        exit(1);
    }


    fseek(retData->pF, 0, SEEK_END); // Sets the file position indicator to the last element in the contiguous block
    retData->fSize = ftell(retData->pF); // ftell returns the offset of the position indicator from the initial address
    rewind(retData->pF); // Returns the position pointer to base

    retData->buffer = malloc(retData->fSize + 1); // +1 for null terminator
    if(retData->buffer == NULL) {
        fclose(retData->pF);
        fprintf(stderr, "ERORR: Memory allocation failure\n");
        exit(1);
    }

    // Read the file contents into the buffer
    fread(retData->buffer, sizeof(char), retData->fSize, retData->pF);
    retData->buffer[retData->fSize] = '\0';


    return retData;
}

void close_file(FileData **file) {;
    if(*file == NULL) return;
    
    if((*file)->pF != NULL) fclose((*file)->pF);
    if((*file)->buffer != NULL) free((*file)->buffer);
    
    free(*file);
    *file = NULL;
}

void write_text(char *fileName, FileData *writeFile) {
    writeFile->pF = fopen(fileName, "w");
    if(writeFile == NULL) {
        perror("ERROR");
        exit(1);
    }

    fprintf(writeFile->pF, "%s", writeFile->buffer);
}