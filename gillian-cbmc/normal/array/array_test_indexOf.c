#include "array.h"
#include <gillian-c/gillian-c.h>

static Array *v1;
static Array *v2;
static ArrayConf vc;
static int stat;

int main() {
    stat = array_new(&v1);

    int a = __nondet_int();
    int b = __nondet_int();
    int c = __nondet_int();

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);

    size_t ai;
    array_index_of(v1, &a, &ai);

    size_t ci;
    array_index_of(v1, &c, &ci);

    __CPROVER_assert(0 == ai, "")
    __CPROVER_assert(2 == ci, "")

    array_destroy(v1);

    return 0;
}
