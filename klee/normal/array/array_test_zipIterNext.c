#include "array.h"
#include "utils.h"
#include <klee/klee.h> 

static Array *v1;
static Array *v2;
static ArrayConf vc;
static int stat;

int main() {
    stat = array_new(&v1);

    char a; klee_make_symbolic(&a, sizeof(char), "a");

    char str_a[] = {a, '\0'};

    char b; klee_make_symbolic(&b, sizeof(char), "b");

    char str_b[] = {b, '\0'};

    char c; klee_make_symbolic(&c, sizeof(char), "c");

    char str_c[] = {c, '\0'};

    char d; klee_make_symbolic(&d, sizeof(char), "d");

    char str_d[] = {d, '\0'};

    char e; klee_make_symbolic(&e, sizeof(char), "e");

    char str_e[] = {e, '\0'};

    char f; klee_make_symbolic(&f, sizeof(char), "f");

    char str_f[] = {f, '\0'};

    char g; klee_make_symbolic(&g, sizeof(char), "g");

    char str_g[] = {g, '\0'};

    array_add(v1, str_a);
    array_add(v1, str_b);
    array_add(v1, str_c);
    array_add(v1, str_d);

    array_new(&v2);

    array_add(v2, str_e);
    array_add(v2, str_f);
    array_add(v2, str_g);

    ArrayZipIter zip;
    array_zip_iter_init(&zip, v1, v2);

    size_t i = 0;

    void *e1, *e2;
    while (array_zip_iter_next(&zip, &e1, &e2) != CC_ITER_END) {
        if (i == 0) {
            CHECK_EQUAL_C_STRING(str_a, (char *)e1);
            CHECK_EQUAL_C_STRING(str_e, (char *)e2);
        }
        if (i == 2) {
            CHECK_EQUAL_C_STRING(str_c, (char *)e1);
            CHECK_EQUAL_C_STRING(str_g, (char *)e2);
        }
        i++;
    }
    klee_assert(3 == i);
    array_destroy(v2);

    array_destroy(v1);

    return 0;
}
