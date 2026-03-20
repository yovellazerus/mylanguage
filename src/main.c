
#include "../inc/common.h"
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
	return 0;
}
