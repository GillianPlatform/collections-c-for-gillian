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
    int d; klee_make_symbolic(&d, sizeof(int), "d");

    int N; klee_make_symbolic(&N, sizeof(int), "N");

    klee_assume(c != a && c != b && c != d && c != N);

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);
    array_add(v1, &d);

    ArrayIter iter;
    array_iter_init(&iter, v1);

    int *e;
    while (array_iter_next(&iter, (void *)&e) != CC_ITER_END) {
        if (*e == c)
            array_iter_add(&iter, &N);
    }

    klee_assert(5 == array_size(v1));

    void *n;
    array_get_at(v1, 3, &n);
    klee_assert(N == *((int *)n));
    klee_assert(1 == array_contains(v1, &N));

    array_get_at(v1, 4, (void *)&n);
    klee_assert(d == *((int *)n));

    array_destroy(v1);

    return 0;
}
