// Local headers
#include <parser.h>
#include <tokenizer.h>

TokenData *run_pipeline(char *data, int fSize) { // TODO: When procedures become more complex parse operations into AST
    TokenData *tokenTail = tokenize_file(data, fSize);
    // Render tokens into AST
    return tokenTail;
}