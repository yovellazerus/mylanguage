
#include "../inc/common.h"
#include "../inc/list.h"
#include "../inc/lexer.h"
#include "../inc/object.h"
#include "../inc/node.h"

Node_t* Add(Node_t* lhs, Node_t* rhs){ return BinaryOp(lhs, rhs, "+");}
Node_t* Sub(Node_t* lhs, Node_t* rhs){ return BinaryOp(lhs, rhs, "-");}
Node_t* Mul(Node_t* lhs, Node_t* rhs){ return BinaryOp(lhs, rhs, "*");}
Node_t* Div(Node_t* lhs, Node_t* rhs){ return BinaryOp(lhs, rhs, "/");}
Node_t* Mod(Node_t* lhs, Node_t* rhs){ return BinaryOp(lhs, rhs, "%");}
Node_t* Or(Node_t* lhs, Node_t* rhs) { return BinaryOp(lhs, rhs, "||");}
Node_t* And(Node_t* lhs, Node_t* rhs){ return BinaryOp(lhs, rhs, "&&");}
Node_t* Xor(Node_t* lhs, Node_t* rhs){ return BinaryOp(lhs, rhs, "^^");}

void ast_dot(const Node_t* root, FILE* file){
    if(!root) return;
    if(!file) file = stdout;
    dot_nid = 0;
    fprintf(file, "digraph AST {\n");
    _(root, _dot, file);
    fprintf(file, "}\n");
}

// =============================================================================
// main
// =============================================================================

void test0(void){
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
        return;
    }
    
    lexer_t* lex = lexer_create(inpath);
    if(!lex){
        perror(inpath);
        return;
    }
    list_t* tokens = lexer_lexall(lex);
    list_dump(tokens, out);
    
    list_destroy(tokens);
    lexer_destroy(lex);
    fclose(out);
}

int main()
{
    Node_t* root = Add(
                        Sub(
                            Literal(Number(3)),
                            Literal(Number(2))
                        ),

                        Literal(Number(-2.5))
                    );

    ast_dot(root, stdout);
    Object_t* res = _(root, _eval);
    _(res, _dump, stdout);

	return 0;
}
