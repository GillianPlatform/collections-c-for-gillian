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

    int replacement = __nondet_int();
    __CPROVER_assume(replacement != c);
    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);

    array_replace_at(v1, &replacement, 2, NULL);

    int *repl;
    array_get_at(v1, 2, (void *)&repl);

    __CPROVER_assert(*repl != c, "");
    __CPROVER_assert(*repl == replacement, "");

    array_destroy(v1);

    return 0;
}
