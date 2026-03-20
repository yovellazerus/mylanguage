
#include "../inc/list.h"

typedef struct node_t {
    struct node_t* next;
    void* item;
} node_t;
static node_t* node_create(const void* item, FNcopy copy){
    if(!copy){
        return NULL;
    } 
    node_t* res = malloc(sizeof(*res));
    if(!res) return NULL;
    res->item = copy(item);
    if(!res->item){
        free(res);
        return NULL;
    }
    res->next = NULL;
    return res;
}
static void    node_destroy(node_t* n, FNdestroy destroy){
    if(!n || ! destroy) return;
    destroy(n->item);
    free(n);
}
static void    node_dump(const node_t* n, FILE* f, FNdump dump){
    if(!f) f = stdout;
    if(!n || !dump){
        fprintf(f, "(null)");
        return;
    }
    dump(n->item, f);
}

struct list_t {
    node_t* head;
    size_t   size;
    FNcopy copy;
    FNdestroy destroy;
    FNdump dump;
};

list_t* list_create(FNcopy copy, 
                    FNdestroy destroy, 
                    FNdump dump){
    if(!copy || !destroy || !dump) return NULL;
    list_t* res = malloc(sizeof(*res));
    if(!res) return NULL;
    res->head = NULL;
    res->size = 0;
    res->copy = copy;
    res->destroy = destroy;
    res->dump = dump;
    return res;
}
void list_destroy(list_t* l){
    if(!l) return;
    node_t* curr = l->head;
    node_t* do_destroy = NULL;
    while(curr){
        do_destroy = curr;
        curr = curr->next;
        node_destroy(do_destroy, l->destroy);
    }
    free(l);
}
void list_dump(const list_t* l, FILE* f){
    if(!f) f = stdout;
    if(!l){
        fprintf(f, "(null)");
        return;
    }
    fprintf(f, "(");
    node_t* curr = l->head;
    while(curr){
        if(curr != l->head) fprintf(f, ", ");
        node_dump(curr, f, l->dump);
        curr = curr->next;
    }
    fprintf(f, ")\n");
}
bool list_push(list_t* l, void* item){
    if(!l || !item) return false;
    if(!l->head){
        l->head = node_create(item, l->copy);
        if(!l->head){
            return false;
        } 
        l->size++;
        return true;
    }
    
    node_t* curr = l->head;
    while(curr->next){
        curr = curr->next;
    }
    curr->next = node_create(item, l->copy);
    if(!curr->next) return false;
    
    l->size++;
    return true;
}
