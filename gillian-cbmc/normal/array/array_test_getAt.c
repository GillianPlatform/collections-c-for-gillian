#include "array.h"

static Array *v1;
static Array *v2;
static ArrayConf vc;
static int stat;

int main() {
    stat = array_new(&v1);

    int a = __nondet_int();
    int b = __nondet_int();
    int c = __nondet_int();
    int e = __nondet_int();

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);
    array_add(v1, &e);

    int *ar;
    int *cr;
    array_get_at(v1, 0, (void *)&ar);
    array_get_at(v1, 2, (void *)&cr);

    __CPROVER_assert(a == *ar, "");
    __CPROVER_assert(c == *cr, "");

    array_destroy(v1);

    return 0;
}
