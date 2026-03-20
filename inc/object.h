#ifndef OBJECT_H_
#define OBJECT_H_

#include "common.h"

// =============================================================================
// Object_t
// =============================================================================

typedef enum   Object_type_t Object_type_t;
typedef struct Object_vt_t Object_vt_t; 
typedef struct Object_t Object_t;

typedef struct Number_t Number_t;
typedef struct Bool_t Bool_t;
typedef struct String_t String_t;

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

// =============================================================================
// Number_t
// =============================================================================

// constructor, Guaranteed to succeed, if there is no memory in the system it will cause a crash.
Object_t* Number(double value);
Object_t* Number_dtor(Object_t* obj);
Object_t* Number_copy(const Object_t* obj);
Object_t* Number_dump(const Object_t* obj, FILE* file);
Object_t* Number_add(const Object_t* obj1, const Object_t* obj2);
Object_t* Number_sub(const Object_t* obj1, const Object_t* obj2);
Object_t* Number_mul(const Object_t* obj1, const Object_t* obj2);
Object_t* Number_div(const Object_t* obj1, const Object_t* obj2);
Object_t* Number_mod(const Object_t* obj1, const Object_t* obj2);
Object_t* Number_or(const Object_t* obj1, const Object_t* obj2);
Object_t* Number_and(const Object_t* obj1, const Object_t* obj2);
Object_t* Number_xor(const Object_t* obj1, const Object_t* obj2);
struct Number_t {
    Object_t base;
    double value;
};
static Object_vt_t Number_vt = {
    ._dtor = Number_dtor,
    ._copy = Number_copy,
    ._dump = Number_dump,
    ._add =  Number_add,
    ._sub =  Number_sub,
    ._mul =  Number_mul,
    ._div = Number_div, 
    ._mod =  Number_mod,
    ._or =  Number_or,
    ._and = Number_and, 
    ._xor = Number_xor,
};

// =============================================================================
// Bool_t
// =============================================================================

// constructor, Guaranteed to succeed, if there is no memory in the system it will cause a crash.
Object_t* Bool(bool value);
Object_t* Bool_dtor(Object_t* obj);
Object_t* Bool_copy(const Object_t* obj);
Object_t* Bool_dump(const Object_t* obj, FILE* file);
Object_t* Bool_add(const Object_t* obj1, const Object_t* obj2);
Object_t* Bool_sub(const Object_t* obj1, const Object_t* obj2);
Object_t* Bool_mul(const Object_t* obj1, const Object_t* obj2);
Object_t* Bool_div(const Object_t* obj1, const Object_t* obj2);
Object_t* Bool_mod(const Object_t* obj1, const Object_t* obj2);
Object_t* Bool_or(const Object_t* obj1, const Object_t* obj2);
Object_t* Bool_and(const Object_t* obj1, const Object_t* obj2);
Object_t* Bool_xor(const Object_t* obj1, const Object_t* obj2);
struct Bool_t {
    Object_t base;
    bool value;
};
static Object_vt_t Bool_vt = {
    ._dtor = Bool_dtor,
    ._copy = Bool_copy,
    ._dump = Bool_dump,
    ._add =  Bool_add,
    ._sub =  Bool_sub,
    ._mul =  Bool_mul,
    ._div = Bool_div, 
    ._mod =  Bool_mod,
    ._or =  Bool_or,
    ._and = Bool_and, 
    ._xor = Bool_xor,
};

// =============================================================================
// String_t
// =============================================================================

// constructor, Guaranteed to succeed, if there is no memory in the system it will cause a crash.
Object_t* String(const char* value);
Object_t* String_dtor(Object_t* obj);
Object_t* String_copy(const Object_t* obj);
Object_t* String_dump(const Object_t* obj, FILE* file);
Object_t* String_add(const Object_t* obj1, const Object_t* obj2);
Object_t* String_sub(const Object_t* obj1, const Object_t* obj2);
Object_t* String_mul(const Object_t* obj1, const Object_t* obj2);
Object_t* String_div(const Object_t* obj1, const Object_t* obj2);
Object_t* String_mod(const Object_t* obj1, const Object_t* obj2);
Object_t* String_or(const Object_t* obj1, const Object_t* obj2);
Object_t* String_and(const Object_t* obj1, const Object_t* obj2);
Object_t* String_xor(const Object_t* obj1, const Object_t* obj2);
struct String_t {
    Object_t base;
    const char* value;
};
static Object_vt_t String_vt = {
    ._dtor = String_dtor,
    ._copy = String_copy,
    ._dump = String_dump,
    ._add =  String_add,
    ._sub =  String_sub,
    ._mul =  String_mul,
    ._div = String_div, 
    ._mod =  String_mod,
    ._or =  String_or,
    ._and = String_and, 
    ._xor = String_xor,
};

#endif // OBJECT_H_