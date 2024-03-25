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

    array_reverse(v1);

    int *i0;
    int *i1;
    int *i2;
    array_get_at(v1, 0, (void *)&i0);
    array_get_at(v1, 1, (void *)&i1);
    array_get_at(v1, 2, (void *)&i2);

    klee_assert(c == *i0);
    klee_assert(b == *i1);
    klee_assert(a == *i2);

    array_destroy(v1);

    return 0;
}
