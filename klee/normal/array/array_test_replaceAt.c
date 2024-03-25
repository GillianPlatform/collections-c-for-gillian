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

    int replacement; klee_make_symbolic(&replacement, sizeof(int), "replacement");
    klee_assume(replacement != c);
    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);

    array_replace_at(v1, &replacement, 2, NULL);

    int *repl;
    array_get_at(v1, 2, (void *)&repl);

    klee_assert(*repl != c);
    klee_assert(*repl == replacement);

    array_destroy(v1);

    return 0;
}
