
#include "../inc/token.h"

static const char* Token_type_to_cstr[] = {
#define X(name) [TOKEN_##name] = #name,
    TOKEN_TYPE_LIST(X)
#undef X
};

token_t* token_create(token_type_t type, char* idnf, size_t row, size_t col, const char* file){
    if(!idnf || !file) return NULL;
    token_t* res = malloc(sizeof(*res));
    if(!res) return NULL;
    res->type = type;
    res->idnf = strdup(idnf);
    res->row = row;
    res->col = col;
    res->file = file;
    return res;
}
void* token_copy(const void* t){
    if(!t) return NULL;
    token_t* tt = (token_t*)t;
    return token_create(tt->type, strdup(tt->idnf), tt->row, tt->col, tt->file);
}
void token_destroy(void* t){
    if(!t) return;
    token_t* tt = (token_t*)t;
    free(tt->idnf);
    free(tt);
}
void token_dump(const void* t, FILE* f){
    if(!f) f = stdout;
    if(!t){
        fprintf(f, "\n(null)");
        return;
    }

    const token_t* tt = (const token_t*)t;

    const char* type_str = Token_type_to_cstr[tt->type] ?
                           Token_type_to_cstr[tt->type] :
                           Token_type_to_cstr[TOKEN_TYPE_COUNT];

    fprintf(f,
        "\n[ %-12s | %-12s | (%3zu, %3zu) | %s ]",
        type_str,
        tt->idnf,
        tt->row,
        tt->col,
        tt->file
    );
    if(tt->type == TOKEN_TYPE_COUNT) fprintf(f, ",\n");
}
