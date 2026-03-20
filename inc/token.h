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
    X(TYPE_eof)            \
    X(TYPE_num)            \
    X(TYPE_str)            \
    X(TYPE_name)           \
    X(TYPE_plus)           \
    X(TYPE_minus)          \
    X(TYPE_asterisk)       \
    X(TYPE_slash)          \
    X(TYPE_percent)        \
    X(TYPE_qmark)          \
    X(TYPE_eq)             \
    X(TYPE_collneq)        \
    X(TYPE_err)

typedef enum {
#define X(name) name,
    TOKEN_TYPE_LIST(X)
#undef X
} token_type_t;

static const char* type_to_cstr[] = {
#define X(name) [name] = #name,
    TOKEN_TYPE_LIST(X)
#undef X
};

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