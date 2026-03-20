#ifndef AST_H_
#define AST_H_

#include "../inc/common.h"
#include "../inc/object.h"

// =============================================================================
// Node_t
// =============================================================================

typedef enum   Node_type_t Node_type_t;
typedef struct Node_vt_t Node_vt_t; 
typedef struct Node_t Node_t;

#define NODE_LIST(X)        \
    X(Literal)              \
    X(BinaryOp)             \
                            \
                            \
    X(TYPE_COUNT)

enum Node_type_t {
#define X(name) NODE_##name,
	NODE_LIST(X)
#undef X
};

static const char* Node_type_to_cstr[] = {
#define X(name) [NODE_##name] = #name,
	NODE_LIST(X)
#undef X
};

// =============================================================================
// Node_t
// =============================================================================

// all methods return Object_t* for _() macro
struct Node_vt_t {
    
    Object_t* (*_dtor)(Node_t*);
    Object_t* (*_eval)(const Node_t*);
    int       (*_dot)(const Node_t*, FILE*);
   // ... 
   
};

// base class
struct Node_t {
    Node_type_t type;
    Node_vt_t*  vt;
};

static int dot_nid = 0;

// constructor, Guaranteed to succeed, if there is no memory in the system it will cause a crash.
Node_t* Literal(Object_t* obj);
Node_t* BinaryOp(Node_t* lhs, Node_t* rhs, const char* op);

#endif // AST_H_