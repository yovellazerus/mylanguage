
#include "../inc/common.h"
#include "../inc/object.h"

// =============================================================================
// Number_t
// =============================================================================

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
Object_vt_t Number_vt = {
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
typedef struct Number_t {
    Object_t base;
    double value;
} Number_t;
Object_t* Number(double value){
    Number_t* res = malloc(sizeof(*res));
    if(!res) RUN_TIME_ERROR("no system memory");
    res->base.type = OBJECT_Number;
    res->base.vt = &Number_vt;
    res->value = value;
    return (Object_t*)res;
}   
Object_t* Number_dtor(Object_t* obj){
    if(!obj) RUN_TIME_ERROR("no object");
    Number_t* n = (Number_t*)obj;
    free(n);
    return obj;
}
Object_t* Number_copy(const Object_t* obj){
    if(!obj) RUN_TIME_ERROR("no object");
    Number_t* n = (Number_t*)obj;
    return Number(n->value);
}
Object_t* Number_dump(const Object_t* obj, FILE* file){
    if(!file) file = stdout;
    if(!obj) RUN_TIME_ERROR("no object");
    Number_t* n = (Number_t*)obj;
    fprintf(file, "%.2lf\n", n->value);
    return (Object_t*)obj; // TODO: what to do with the const??
}
Object_t* Number_add(const Object_t* obj1, const Object_t* obj2){
    if(!obj1 || !obj2) RUN_TIME_ERROR("no object");
    const Number_t* a = (const Number_t*)obj1;
    const Number_t* b = (const Number_t*)obj2;
    return Number(a->value + b->value);
}
Object_t* Number_sub(const Object_t* obj1, const Object_t* obj2){
    if(!obj1 || !obj2) RUN_TIME_ERROR("no object");
    const Number_t* a = (const Number_t*)obj1;
    const Number_t* b = (const Number_t*)obj2;
    return Number(a->value - b->value);
}
Object_t* Number_mul(const Object_t* obj1, const Object_t* obj2){
    if(!obj1 || !obj2) RUN_TIME_ERROR("no object");
    const Number_t* a = (const Number_t*)obj1;
    const Number_t* b = (const Number_t*)obj2;
    return Number(a->value * b->value);
}
Object_t* Number_div(const Object_t* obj1, const Object_t* obj2){
    if(!obj1 || !obj2) RUN_TIME_ERROR("no object");
    const Number_t* a = (const Number_t*)obj1;
    const Number_t* b = (const Number_t*)obj2;
    if(b->value == 0.0) RUN_TIME_ERROR("divition by zero error");
    return Number(a->value / b->value);
}
Object_t* Number_mod(const Object_t* obj1, const Object_t* obj2){
    RUN_TIME_ERROR("not sported for type Number");
}
Object_t* Number_or(const Object_t* obj1, const Object_t* obj2){
    RUN_TIME_ERROR("not sported for type Number");
}
Object_t* Number_and(const Object_t* obj1, const Object_t* obj2){
    RUN_TIME_ERROR("not sported for type Number");
}
Object_t* Number_xor(const Object_t* obj1, const Object_t* obj2){
    RUN_TIME_ERROR("not sported for type Number");
}

// =============================================================================
// Bool_t
// =============================================================================

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
typedef struct Bool_t {
    Object_t base;
    bool value;
} Bool_t;
Object_t* Bool(bool value){
    Bool_t* res = malloc(sizeof(*res));
    if(!res) RUN_TIME_ERROR("no system memory");
    res->base.type = OBJECT_Bool;
    res->base.vt = &Bool_vt;
    res->value = value;
    return (Object_t*)res;
}   
Object_t* Bool_dtor(Object_t* obj){
    Bool_t* b = (Bool_t*)obj;
    free(b);
    return obj;
}
Object_t* Bool_copy(const Object_t* obj){
    if(!obj) RUN_TIME_ERROR("no object");
    Bool_t* b = (Bool_t*)obj;
    return Bool(b->value);
}
Object_t* Bool_dump(const Object_t* obj, FILE* file){
    if(!file) file = stdout;
    if(!obj) RUN_TIME_ERROR("no object");
    Bool_t* b = (Bool_t*)obj;
    fprintf(file, "%s\n", b->value ? "True" : "False");
    return (Object_t*)obj; // TODO: what to do with the const??
}
Object_t* Bool_add(const Object_t* obj1, const Object_t* obj2){
    RUN_TIME_ERROR("not sported for type Bool");
}
Object_t* Bool_sub(const Object_t* obj1, const Object_t* obj2){
    RUN_TIME_ERROR("not sported for type Bool");
}
Object_t* Bool_mul(const Object_t* obj1, const Object_t* obj2){
    RUN_TIME_ERROR("not sported for type Bool");
}
Object_t* Bool_div(const Object_t* obj1, const Object_t* obj2){
    RUN_TIME_ERROR("not sported for type Bool");
}
Object_t* Bool_mod(const Object_t* obj1, const Object_t* obj2){
    RUN_TIME_ERROR("not sported for type Bool");
}
Object_t* Bool_or(const Object_t* obj1, const Object_t* obj2){
    if(!obj1 || !obj2) RUN_TIME_ERROR("no object");
    const Bool_t* a = (const Bool_t*)obj1;
    const Bool_t* b = (const Bool_t*)obj2;
    return Bool(a->value || b->value);
}
Object_t* Bool_and(const Object_t* obj1, const Object_t* obj2){
    if(!obj1 || !obj2) RUN_TIME_ERROR("no object");
    const Bool_t* a = (const Bool_t*)obj1;
    const Bool_t* b = (const Bool_t*)obj2;
    return Bool(a->value && b->value);
}
Object_t* Bool_xor(const Object_t* obj1, const Object_t* obj2){
    if(!obj1 || !obj2) RUN_TIME_ERROR("no object");
    const Bool_t* a = (const Bool_t*)obj1;
    const Bool_t* b = (const Bool_t*)obj2;
    return Bool((a->value && !b->value) || (!a->value && b->value));
}

// =============================================================================
// String_t
// =============================================================================

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
typedef struct String_t {
    Object_t base;
    const char* value;
} String_t;
Object_t* String(const char* value){
    String_t* res = malloc(sizeof(*res));
    if(!res) RUN_TIME_ERROR("no system memory");
    res->base.type = OBJECT_String;
    res->base.vt = &String_vt;
    res->value = strdup(value);
    if(!res->value){
        free(res);
        RUN_TIME_ERROR("no system memory");
    }
    return (Object_t*)res;
}   
Object_t* String_dtor(Object_t* obj){
    String_t* s = (String_t*)obj;
    free((char*)s->value);
    free(s);
    return obj;
}
Object_t* String_copy(const Object_t* obj){
    String_t* s = (String_t*)obj;
    return String(s->value);
}
Object_t* String_dump(const Object_t* obj, FILE* file){
    if(!file) file = stdout;
    if(!obj)  RUN_TIME_ERROR("no object");
    String_t* s = (String_t*)obj;
    fprintf(file, "%s\n", s->value ? s->value : "(null)");
    return (Object_t*)obj; // TODO: what to do with the const??
}
Object_t* String_add(const Object_t* obj1, const Object_t* obj2){
    if(!obj1 || !obj2) RUN_TIME_ERROR("no object");
    const String_t* a = (const String_t*)obj1;
    const String_t* b = (const String_t*)obj2;
    size_t na = strlen(a->value);
    size_t nb = strlen(b->value);
    size_t nn = na + nb;
    char* tmp = malloc(nn + 1);
    if(!tmp) RUN_TIME_ERROR("no system memory");
    int i;
    for(i = 0; i < na; i++){
        tmp[i] = a->value[i];
    }
    for(i = 0; i < nb; i++){
        tmp[i + na] = b->value[i];
    }
    tmp[nn] = '\0';
    Object_t* res = String(tmp);
    free(tmp);
    return res;
}
Object_t* String_sub(const Object_t* obj1, const Object_t* obj2){
    RUN_TIME_ERROR("not sported for type String");
}
Object_t* String_mul(const Object_t* obj1, const Object_t* obj2){
    RUN_TIME_ERROR("not sported for type String");
}
Object_t* String_div(const Object_t* obj1, const Object_t* obj2){
    RUN_TIME_ERROR("not sported for type String");
}
Object_t* String_mod(const Object_t* obj1, const Object_t* obj2){
    RUN_TIME_ERROR("not sported for type String");
}
Object_t* String_or(const Object_t* obj1, const Object_t* obj2){
    RUN_TIME_ERROR("not sported for type String");
}
Object_t* String_and(const Object_t* obj1, const Object_t* obj2){
    RUN_TIME_ERROR("not sported for type String");
}
Object_t* String_xor(const Object_t* obj1, const Object_t* obj2){
    RUN_TIME_ERROR("not sported for type String");
}
