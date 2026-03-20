#ifndef LIST_H_
#define LIST_H_

#include "../inc/common.h"

// =============================================================================
// list_t
// =============================================================================

typedef void* (*FNcopy)(const void*);
typedef void  (*FNdestroy)(void*);
typedef void  (*FNdump)(const void*, FILE*);

typedef struct list_t list_t;
list_t* list_create(FNcopy copy, 
                    FNdestroy destroy, 
                    FNdump dump);
void list_destroy(list_t* l);
void list_dump(const list_t* l, FILE* f);
bool list_push(list_t* l, void* item);

#endif // LIST_H_