#include <assert.h>
#include <stdio.h>

#include "array.h"

static Array *v1;
static Array *v2;
static ArrayConf vc;
static int stat;

void CHECK_EQUAL_C_STRING(char *s1, char *s2) { assert(strcmp(s1, s2) == 0); }

int main() {
    stat = array_new(&v1);

    // These values were extracted from the CBMC(v5.95.1) counter example for
    // that tests. CBMC claims that the assert on line 49 is failing.
    // However, one can run this program with fsanitize, and check that there is
    // no failure. Therefore, this is a false positive.
    char str_a[] = "H";
    char str_b[] = {8, 0};
    char str_c[] = "\t";
    char str_d[] = "H";
    char str_e[] = "@";
    char str_f[] = "@";
    char str_g[] = "@";

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
    assert(0 == array_contains(v1, str_b));
    assert(0 == array_contains(v2, str_f));
    assert(3 == array_size(v1));
    assert(2 == array_size(v2));

    array_destroy(v2);

    array_destroy(v1);

    printf("success");
    return 0;
}
