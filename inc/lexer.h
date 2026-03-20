#ifndef LEXER_H_
#define LEXER_H_

#include "../inc/common.h"
#include "../inc/token.h"
#include "../inc/list.h"

// =============================================================================
// lexer_t
// =============================================================================

typedef struct lexer_t lexer_t;

lexer_t* lexer_create(const char* path);
void     lexer_destroy(lexer_t* lex);
void     lexer_lexcomment(lexer_t* lex);
token_t* lexer_lexnum(lexer_t* lex);
// TODO: no escape for now...
token_t* lexer_lexstr(lexer_t* lex);
token_t* lexer_lexname(lexer_t* lex);
token_t* lexer_lexop(lexer_t* lex);
token_t* lexer_nextok(lexer_t* lex);
// main lexer function
list_t*  lexer_lexall(lexer_t* lex);

#endif // LEXER_H_