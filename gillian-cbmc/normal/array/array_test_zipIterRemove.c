#include "array.h"
#include "utils.h"
#include <gillian-c/gillian-c.h>

static Array *v1;
static Array *v2;
static ArrayConf vc;
static int stat;

int main() {
    stat = array_new(&v1);

    char a = __nondet_int();

    char str_a[] = {a, '\0'};

    char b = __nondet_int();

    char str_b[] = {b, '\0'};

    char c = __nondet_int();

    char str_c[] = {c, '\0'};

    char d = __nondet_int();

    char str_d[] = {d, '\0'};

    char e = __nondet_int();

    char str_e[] = {e, '\0'};

    char f = __nondet_int();

    char str_f[] = {f, '\0'};

    char g = __nondet_int();

    char str_g[] = {g, '\0'};

    __CPROVER_assume((!(strcmp(str_a, str_b) == 0)) && (!(strcmp(str_c, str_b) == 0)) &&
           (!(strcmp(str_d, str_b) == 0)));

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

    void *e1, *e2;
    void *r1, *r2;
    while (array_zip_iter_next(&zip, &e1, &e2) != CC_ITER_END) {
        if (strcmp((char *)e1, str_b) == 0)
            array_zip_iter_remove(&zip, &r1, &r2);
    }
    CHECK_EQUAL_C_STRING(str_b, (char *)r1);
    __CPROVER_assert(0 == array_contains(v1, str_b), "")
    __CPROVER_assert(0 == array_contains(v2, str_f), "")
    __CPROVER_assert(3 == array_size(v1), "")
    __CPROVER_assert(2 == array_size(v2), "")

    array_destroy(v2);

    array_destroy(v1);

    return 0;
}
