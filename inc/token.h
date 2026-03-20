#ifndef TOKEN_H_
#define TOKEN_H_

#include "../inc/common.h"

// =============================================================================
// token_t
// =============================================================================

/*
Their names were given according to the symbols themselves
and not according to their syntactic meaning.
*/
// NOTE: TYPE_err must be last!
#define TOKEN_TYPE_LIST(X) \
    X(eof)            \
    X(num)            \
    X(str)            \
    X(name)           \
    X(plus)           \
    X(minus)          \
    X(asterisk)       \
    X(slash)          \
    X(percent)        \
    X(qmark)          \
    X(eq)             \
    X(collneq)        \
    X(err)            \
    X(TYPE_COUNT)

typedef enum {
#define X(name) TOKEN_##name,
    TOKEN_TYPE_LIST(X)
#undef X
} token_type_t;

typedef struct token_t {
    token_type_t type;
    char* idnf;
    size_t row;
    size_t col;
    const char*  file;
} token_t;
token_t* token_create(token_type_t type, char* idnf, size_t row, size_t col, const char* file);
void* token_copy(const void* t);
void token_destroy(void* t);
void token_dump(const void* t, FILE* f);

#endif // TOKEN_H_