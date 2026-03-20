
#include "../inc/node.h"

// =============================================================================
// Literal_t
// =============================================================================

Object_t* Literal_dtor(Node_t* node);
Object_t* Literal_eval(const Node_t* node);
int       Literal_dot(const Node_t* node, FILE* file);
Node_vt_t Literal_vt = {
    ._dtor = Literal_dtor,
    ._eval = Literal_eval,
    ._dot = Literal_dot,
};
typedef struct Literal_t {
    Node_t base;
    Object_t* value;
} Literal_t;

Node_t* Literal(Object_t* obj){
    Literal_t* res = malloc(sizeof(*res));
    if(!res) RUN_TIME_ERROR("no system memory");
    res->base.type = NODE_Literal;
    res->base.vt = &Literal_vt;
    res->value = obj;
    return (Node_t*)res;
}
Object_t* Literal_dtor(Node_t* node){
    if(!node) RUN_TIME_ERROR("no node");
    Literal_t* l = (Literal_t*)node;
    return _(l->value, _dtor);
}
Object_t* Literal_eval(const Node_t* node){
    if(!node) RUN_TIME_ERROR("no node");
    Literal_t* l = (Literal_t*)node;
    return l->value;
}
// leaf node
int Literal_dot(const Node_t* node, FILE* file){
    if(!node) RUN_TIME_ERROR("no node");
    Literal_t* l = (Literal_t*)node;
    int my_id = dot_nid++;
    
    fprintf(file, "\t%d [label=\"", my_id);
    
    _(l->value, _dump, file);
    
    fprintf(file, "\"]\n");
    return my_id;
}

// =============================================================================
// BinaryOp_t
// =============================================================================

Object_t* BinaryOp_dtor(Node_t* node);
Object_t* BinaryOp_eval(const Node_t* node);
int       BinaryOp_dot(const Node_t* node, FILE* file);
Node_vt_t BinaryOp_vt = {
    ._dtor = BinaryOp_dtor,
    ._eval = BinaryOp_eval,
    ._dot = BinaryOp_dot,
};
typedef struct BinaryOp_t {
    Node_t base;
    Node_t* lhs;
    Node_t* rhs;
    const char* op;
} BinaryOp_t;

Node_t* BinaryOp(Node_t* lhs, Node_t* rhs, const char* op){
    BinaryOp_t* res = malloc(sizeof(*res));
    if(!res) RUN_TIME_ERROR("no system memory");
    res->base.type = NODE_BinaryOp;
    res->base.vt = &BinaryOp_vt;
    
    res->lhs = lhs;
    res->rhs = rhs;
    res->op = op;

    return (Node_t*)res;
}
Object_t* BinaryOp_dtor(Node_t* node){
    if(!node) RUN_TIME_ERROR("no node");
    BinaryOp_t* b = (BinaryOp_t*)node;
    _(b->lhs, _dtor);
    return _(b->rhs, _dtor);
}
Object_t* BinaryOp_eval(const Node_t* node){
    if(!node) RUN_TIME_ERROR("no node");
    BinaryOp_t* b = (BinaryOp_t*)node;
    const char* op = b->op;
    Node_t* lhs = b->lhs;
    Node_t* rhs = b->rhs;
    Object_t* el = _(lhs, _eval);
    Object_t* er = _(rhs, _eval);

    if(strcmp(op, "+") == 0){
        return _(el, _add, er);
    }
    else if(strcmp(op, "-") == 0){
        return _(el, _sub, er);
    }
    else if(strcmp(op, "*") == 0){
        return _(el, _mul, er);
    }
    else if(strcmp(op, "/") == 0){
        return _(el, _div, er);
    }
    else if(strcmp(op, "%") == 0){
        return _(el, _mod, er);
    }
    else if(strcmp(op, "||") == 0){
        return _(el, _or, er);
    }
    else if(strcmp(op, "&&") == 0){
        return _(el, _and, er);
    }
    else if(strcmp(op, "^^") == 0){
        return _(el, _xor, er);
    }

    // error
    else{
        RUN_TIME_ERROR("unkown binary operation: \"%s\"", op);
    }
    return NULL;
}

int BinaryOp_dot(const Node_t* node, FILE* file){
    if(!node) RUN_TIME_ERROR("no node");
    BinaryOp_t* b = (BinaryOp_t*)node;

    // print the node itself
    int my_id = dot_nid++;
    fprintf(file, "\t%d [label=\"%s\"]\n", my_id, b->op);

    // ege to lhs
    fprintf(file, "\t%d -> %d\n", my_id, _(b->lhs, _dot, file));
    

    // ege to rhs
    fprintf(file, "\t%d -> %d\n", my_id, _(b->rhs, _dot, file));
    

    return my_id;
}
