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
    int d = __nondet_int();

    int N = __nondet_int();

    __CPROVER_assume(c != a && c != b && c != d && c != N);

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

    __CPROVER_assert(5 == array_size(v1), "")

    void *n;
    array_get_at(v1, 3, &n);
    __CPROVER_assert(N == *((int *)n), "")
    __CPROVER_assert(1 == array_contains(v1, &N), "")

    array_get_at(v1, 4, (void *)&n);
    __CPROVER_assert(d == *((int *)n), "")

    array_destroy(v1);

    return 0;
}
