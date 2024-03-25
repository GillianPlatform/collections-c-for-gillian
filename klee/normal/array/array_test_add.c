#include "array.h"
#include <klee/klee.h> 

static Array *v1;
static Array *v2;
static ArrayConf vc;
static int stat;

int main() {
    stat = array_new(&v1);
    klee_assert(stat == CC_OK);

    int a; klee_make_symbolic(&a, sizeof(int), "a");
    int b; klee_make_symbolic(&b, sizeof(int), "b");
    int c; klee_make_symbolic(&c, sizeof(int), "c");

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);

    int *ar;
    int *br;
    int *cr;

    array_get_at(v1, 0, (void *)&ar);
    array_get_at(v1, 1, (void *)&br);
    array_get_at(v1, 2, (void *)&cr);

    klee_assert(a == *ar);
    klee_assert(b == *br);
    klee_assert(c == *cr);

    array_destroy(v1);

    return 0;
}
