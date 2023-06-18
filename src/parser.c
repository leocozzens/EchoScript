// Local headers
#include <parser.h>
#include <tokenizer.h>

TokenData *run_pipeline(char *data, size_t fSize) { // TODO: When procedures become more complex parse operations into AST
    TokenData *tokenHead = tokenize_file(data, fSize);
    // Render tokens into AST
    return tokenHead;
}