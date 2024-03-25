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
    int e; klee_make_symbolic(&e, sizeof(int), "e");

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);
    array_add(v1, &e);

    array_remove_at(v1, 2, NULL);

    klee_assert(3 == array_size(v1));

    int *r;
    array_get_at(v1, 2, (void *)&r);

    klee_assert(r == &e);

    array_destroy(v1);

    return 0;
}
