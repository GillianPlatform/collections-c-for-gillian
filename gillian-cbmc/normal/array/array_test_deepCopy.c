#include "array.h"
#include "utils.h"

static Array *v1;
static Array *v2;
static ArrayConf vc;
static int stat;

int main() {
    stat = array_new(&v1);

    int a = __nondet_int();
    int b = __nondet_int();
    int c = __nondet_int();

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);

    array_copy_deep(v1, copy, &v2);

    __CPROVER_assert(array_size(v2) == array_size(v1), "");

    int *ca;
    array_get_at(v2, 0, (void *)&ca);

    __CPROVER_assert(a == *ca, "");
    array_destroy_cb(v2, free);

    array_destroy(v1);

    return 0;
}
