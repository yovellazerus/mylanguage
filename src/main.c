
#include "../inc/common.h"
#include "../inc/list.h"
#include "../inc/lexer.h"
#include "../inc/object.h"

// =============================================================================
// main
// =============================================================================

int main()
{
    Object_t* n = Number(3.14);
    Object_t* b = Bool(true);
    
    Object_t* s1 = String("hello");
    Object_t* s2 = String(" world!");
    
    Object_t* s3 = _(s1, _add, s2);
    
    _(n, _dump, NULL);
    _(b, _dump, NULL);
    _(s1, _dump, NULL);
    _(s2, _dump, NULL);
    _(s3, _dump, NULL);
    
    _(s1, _dtor);
    _(s2, _dtor);
    _(s3, _dtor);
    _(n, _dtor);
    _(b, _dtor);

    const char* outpath = "C:\\Users\\yovel\\Desktop\\VScode\\mylanguage\\test\\output\\test0.txt";
    const char* inpath = "C:\\Users\\yovel\\Desktop\\VScode\\mylanguage\\test\\input\\test0.txt";
    FILE* out = fopen(outpath, "w");
    if(!out){
        perror(outpath);
        return 1;
    }
    
    lexer_t* lex = lexer_create(inpath);
    if(!lex){
        perror(inpath);
        return 1;
    }
    list_t* tokens = lexer_lexall(lex);
    list_dump(tokens, out);
    
    list_destroy(tokens);
    lexer_destroy(lex);
    fclose(out);

	return 0;
}
