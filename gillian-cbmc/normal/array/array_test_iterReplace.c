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

    int replacement = __nondet_int();

    __CPROVER_assume(c != a && c != b && c != d && c != replacement);

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);
    array_add(v1, &d);

    ArrayIter iter;
    array_iter_init(&iter, v1);

    int *e;
    int *old;
    while (array_iter_next(&iter, (void *)&e) != CC_ITER_END) {
        if (*e == c)
            array_iter_replace(&iter, (void *)&replacement, (void *)&old);
    }

    size_t index;
    array_index_of(v1, (void *)&replacement, &index);

    __CPROVER_assert(2 == index, "")
    __CPROVER_assert(0 == array_contains(v1, &c), "")

    array_destroy(v1);

    return 0;
}
