
#include "../inc/lexer.h"

static inline char* strndup(const char *s, size_t n) {
    size_t len = strnlen(s, n); 
    char *copy = malloc(len + 1);
    if (!copy) return NULL;
    memcpy(copy, s, len);
    copy[len] = '\0';
    return copy;
}

struct lexer_t {
    char* src;
    size_t src_size;
    
    size_t start;
    size_t end; // the lead ptr
    
    const char* file_name;
    size_t row;
    size_t col;
} ;

lexer_t* lexer_create(const char* path){
    lexer_t* res = malloc(sizeof(*res));
    if(!res) return NULL;
    
    if(!path) return NULL;
    FILE* file = fopen(path, "r"); 
    if (file == NULL) {
        return NULL;
    }
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return NULL;
    }
    long size = ftell(file);
    if (size == -1) {
        fclose(file);
        return NULL;
    }
    fseek(file, 0, SEEK_SET);
    
    char* src = malloc(size);
    if(!src){
        fclose(file);
        free(res);
        return NULL;
    }
    src[size] = '\0';
    fread(src, 1, size, file);
    fclose(file);
    
    res->src = src;
    res->src_size = size;
    res->start = 0;
    res->end = 0;
    res->file_name = path;
    res->row = 1;
    res->col = 1;
    
    return res;
}
void     lexer_destroy(lexer_t* lex){
    if(!lex) return;
    free(lex->src);
    free(lex);
}
void lexer_trim(lexer_t* lex){
    if(!lex) return;

    while(lex->src[lex->end] && isspace(lex->src[lex->end])){
        if(lex->src[lex->end] == '\n'){
            lex->row++;
            lex->col = 1;
        } else {
            lex->col++;
        }
        lex->end++;
    }

    lex->start = lex->end;
}
void     lexer_lexcomment(lexer_t* lex){
    if(!lex) return;
    while(lex->src[lex->end] && lex->src[lex->end] != '\n'){
        lex->end++;
        lex->col++;
    }
    if(lex->src[lex->end] == '\n'){
        lex->end++;
        lex->row++;
        lex->col = 1;
    }
    lex->start = lex->end;
}
token_t* lexer_lexnum(lexer_t* lex){
    if(!lex) return NULL;

    char* start_ptr = lex->src + lex->end;
    char* end_ptr = NULL;

    strtof(start_ptr, &end_ptr);

    size_t len = (size_t)(end_ptr - start_ptr);
    if(len == 0) return NULL;

    char* buf = strndup(start_ptr, len);
    if(!buf) return NULL;

    token_t* res = token_create(TYPE_num, buf, lex->row, lex->col, lex->file_name);
    free(buf);

    lex->end += len;
    lex->col += len;
    lex->start = lex->end;

    return res;
}
// TODO: no escape for now...
token_t* lexer_lexstr(lexer_t* lex){
    if(!lex) return NULL;

    // save start position
    size_t row = lex->row;
    size_t col = lex->col;

    // skip opening quote
    lex->end++;
    lex->col++;

    size_t start = lex->end;

    while(lex->src[lex->end] && lex->src[lex->end] != '"'){
        
        if(lex->src[lex->end] == '\n'){
            // strings cannot span lines (for now)
            char* err = strndup(lex->src + start, lex->end - start);
            token_t* res = token_create(TYPE_err, err ? err : "", row, col, lex->file_name);
            free(err);
            return res;
        }

        lex->end++;
        lex->col++;
    }

    // EOF before closing quote → error
    if(lex->src[lex->end] != '"'){
        char* err = strndup(lex->src + start, lex->end - start);
        token_t* res = token_create(TYPE_err, err ? err : "", row, col, lex->file_name);
        free(err);
        return res;
    }

    // extract string content (without quotes)
    size_t len = lex->end - start;

    char* buf = strndup(lex->src + start, len);
    if(!buf) return NULL;

    token_t* res = token_create(TYPE_str, buf, row, col, lex->file_name);
    free(buf);

    // skip closing quote
    lex->end++;
    lex->col++;

    lex->start = lex->end;

    return res;
}
token_t* lexer_lexname(lexer_t* lex){
    if(!lex) return NULL;

    size_t start = lex->end;
    size_t col = lex->col;

    while(lex->src[lex->end] &&
         (isalpha(lex->src[lex->end]) ||
          isdigit(lex->src[lex->end]) ||
          lex->src[lex->end] == '_')){
        lex->end++;
        lex->col++;
    }

    size_t len = lex->end - start;
    if(len == 0) return NULL;

    char* buf = strndup(lex->src + start, len);
    if(!buf) return NULL;

    token_t* res = token_create(TYPE_name, buf, lex->row, col, lex->file_name);
    free(buf);

    lex->start = lex->end;

    return res;
}
token_t* lexer_lexop(lexer_t* lex){
    if(!lex) return NULL;

    char c = lex->src[lex->end];
    token_t* res = NULL;

    switch (c) {

        case '+':
            res = token_create(TYPE_plus, "+", lex->row, lex->col, lex->file_name);
            lex->end++;
            lex->col++;
            break;

        case '-':
            res = token_create(TYPE_minus, "-", lex->row, lex->col, lex->file_name);
            lex->end++;
            lex->col++;
            break;

        case '*':
            res = token_create(TYPE_asterisk, "*", lex->row, lex->col, lex->file_name);
            lex->end++;
            lex->col++;
            break;

        case '/':
            res = token_create(TYPE_slash, "/", lex->row, lex->col, lex->file_name);
            lex->end++;
            lex->col++;
            break;

        case '%':
            res = token_create(TYPE_percent, "%", lex->row, lex->col, lex->file_name);
            lex->end++;
            lex->col++;
            break;

        case '?':
            res = token_create(TYPE_qmark, "?", lex->row, lex->col, lex->file_name);
            lex->end++;
            lex->col++;
            break;

        case '=':
            res = token_create(TYPE_eq, "=", lex->row, lex->col, lex->file_name);
            lex->end++;
            lex->col++;
            break;

        case ':':
            if(lex->src[lex->end + 1] == '='){
                res = token_create(TYPE_collneq, ":=", lex->row, lex->col, lex->file_name);
                lex->end += 2;
                lex->col += 2;
            } else {
                char tmp[2] = {c, '\0'};
                res = token_create(TYPE_err, tmp, lex->row, lex->col, lex->file_name);
                lex->end++;
                lex->col++;
            }
            break;

        default: {
            char tmp[2] = {c, '\0'};
            res = token_create(TYPE_err, tmp, lex->row, lex->col, lex->file_name);
            lex->end++;
            lex->col++;
            break;
        }
    }

    lex->start = lex->end;
    return res;
}
token_t* lexer_nextok(lexer_t* lex){
    if(!lex) return NULL;
    token_t* res = NULL;
    
    
    while(lex->src[lex->end]){
        
        // trim wight space
        if(isspace(lex->src[lex->end])){
            lexer_trim(lex);
            continue;
        }
        
        // comment
        else if(lex->src[lex->end] == '#'){
            lexer_lexcomment(lex);
            continue;
        }
        
        // string: "hello" ...
        else if(lex->src[lex->end] == '"'){
            return lexer_lexstr(lex);
        }
        
        // number: 3.14, 6, 0xFC54
        else if(isdigit(lex->src[lex->end])){
            return lexer_lexnum(lex);
        }
        
        // name: x, foo, _foo12_t ...
        else if(isalpha(lex->src[lex->end]) || lex->src[lex->end] == '_'){
            return lexer_lexname(lex);
        }
        
        // symbol, opertion or an error
        else{
            return lexer_lexop(lex);
        }
    }
    
    // end of the surce file
    return token_create(TYPE_eof, "<EOF>", lex->row, lex->col, lex->file_name);
}
// main lexer function
list_t*  lexer_lexall(lexer_t* lex){
    if(!lex) return NULL;
    list_t* res = list_create(token_copy, token_destroy, token_dump);
    if(!res) return NULL;
    
    token_t* tok = NULL;
    do{
        tok = lexer_nextok(lex); // list_push will not push if null
        list_push(res, tok);
    } while(tok->type != TYPE_eof);
    
    return res;
}
