// C standard headers
#include <stdlib.h>
#include <errno.h>

#define CHECK_ERR(_COND, _ERR) if(_COND) { errno = _ERR; return NULL; }

static unsigned int str_get_len(const char *str);
static char *stp_copy(char *dst, const char *src);

// External functions
char *str_combine(unsigned int count, char **strings) {
    CHECK_ERR(count == 0, EINVAL);

    unsigned int totalLength = 0;
    for(unsigned int i = 0; i < count; i++)
        totalLength += str_get_len(strings[i]);
    
    char *out = malloc(totalLength + 1);
    CHECK_ERR(out == NULL, ENOMEM);
    char *tmp = out;
    for(unsigned int i = 0; i < count; i++)
        tmp = stp_copy(tmp, strings[i]);
    return out;
}

// Local functions
static unsigned int str_get_len(const char *str) {
    unsigned int i = 0;
    for(; *str != '\0'; i++, str++);
    return i;
}

static char *stp_copy(char *dst, const char *src) {
    while(*src != '\0') *dst++ = *src++;
    *dst = '\0';
    return dst;
}