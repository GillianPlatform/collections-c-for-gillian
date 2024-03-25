#include "array.h"
#include <klee/klee.h> 

static Array *v1;
static Array *v2;
static ArrayConf vc;
static int stat;

int main() {
    stat = array_new(&v1);

    int a; klee_make_symbolic(&a, sizeof(int), "a");
    int b; klee_make_symbolic(&b, sizeof(int), "b");
    int c; klee_make_symbolic(&c, sizeof(int), "c");

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);

    size_t ai;
    array_index_of(v1, &a, &ai);

    size_t ci;
    array_index_of(v1, &c, &ci);

    klee_assert(0 == ai);
    klee_assert(2 == ci);

    array_destroy(v1);

    return 0;
}
