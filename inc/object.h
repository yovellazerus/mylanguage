#ifndef OBJECT_H_
#define OBJECT_H_

#include "common.h"

// =============================================================================
// Object_t
// =============================================================================

typedef enum   Object_type_t Object_type_t;
typedef struct Object_vt_t Object_vt_t; 
typedef struct Object_t Object_t;

#define OBJECT_LIST(X)      \
    X(None)                 \
    X(Number)               \
    X(Bool)                 \
    X(String)               \
                            \
                            \
                            \
    X(TYPE_COUNT)

enum Object_type_t {
#define X(name) OBJECT_##name,
	OBJECT_LIST(X)
#undef X
};

static const char* Object_type_to_cstr[] = {
#define X(name) [OBJECT_##name] = #name,
	OBJECT_LIST(X)
#undef X
};

// =============================================================================
// Object_t
// =============================================================================

// all methods return Object_t* for _() macro
struct Object_vt_t {
    // memory
    Object_t*  (*_dtor)(Object_t*);
    Object_t*  (*_copy)(const Object_t*);
    // IO
    Object_t*  (*_dump)(const Object_t*, FILE*);
    // basic operations
    Object_t*  (*_add)(const Object_t*, const Object_t*);
    Object_t*  (*_sub)(const Object_t*, const Object_t*);
    Object_t*  (*_mul)(const Object_t*, const Object_t*);
    Object_t*  (*_div)(const Object_t*, const Object_t*);
    Object_t*  (*_mod)(const Object_t*, const Object_t*);
    Object_t*  (*_or)(const Object_t*, const Object_t*);
    Object_t*  (*_and)(const Object_t*, const Object_t*);
    Object_t*  (*_xor)(const Object_t*, const Object_t*);
   // ... 
   
};

// base class
struct Object_t {
    Object_type_t type;
    Object_vt_t*  vt;
};

// constructor, Guaranteed to succeed, if there is no memory in the system it will cause a crash.
Object_t* Number(double value);
Object_t* Bool(bool value);
Object_t* String(const char* value);

#endif // OBJECT_H_