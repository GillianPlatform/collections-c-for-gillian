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
    int f; klee_make_symbolic(&f, sizeof(int), "f");

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);
    array_add(v1, &e);
    array_add(v1, &f);

    Array *sub;
    array_subarray(v1, 1, 3, &sub);

    klee_assert(3 == array_size(sub));

    int *s0;
    int *s1;
    int *s2;
    array_get_at(sub, 0, (void *)&s0);
    array_get_at(sub, 1, (void *)&s1);
    array_get_at(sub, 2, (void *)&s2);

    klee_assert(&b == s0);
    klee_assert(&c == s1);
    klee_assert(&e == s2);

    array_destroy(sub);

    array_destroy(v1);

    return 0;
}
