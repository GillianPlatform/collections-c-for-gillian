#include "array.h"
#include "utils.h"
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

    array_copy_deep(v1, copy, &v2);

    klee_assert(array_size(v2) == array_size(v1));

    int *ca;
    array_get_at(v2, 0, (void *)&ca);

    klee_assert(a == *ca);
    array_destroy_cb(v2, free);

    array_destroy(v1);

    return 0;
}
