#include "slist.h"
#include "utils.h"
#include <gillian-c/gillian-c.h>

static SList *list;
static SList *list2;
static int stat;

void setup_test() {
    stat = slist_new(&list);
    slist_new(&list2);
};

void teardown_test() {
    slist_destroy(list);
    slist_destroy(list2);
};

int main() {
    setup_test();
    symb_str(a);
    symb_str(b);
    symb_str(c);
    symb_str(d);
    symb_str(e);
    symb_str(f);
    symb_str(g);
    symb_str(h);
    symb_str(i);

    ASSUME(b != a && b != c && b != d);
    ASSUME(f != e && f != g);
    ASSUME(e != g);
    // ASSUME(h != a && h != b && h != c && h != d);
    // ASSUME(c != a && c != d);
    // ASSUME(i != e && i != f && i != g);

    slist_add(list, str_a);
    slist_add(list, str_b);
    slist_add(list, str_c);
    slist_add(list, str_d);

    slist_add(list2, str_e);
    slist_add(list2, str_f);
    slist_add(list2, str_g);

    SListZipIter zip;
    slist_zip_iter_init(&zip, list, list2);

    void *e1, *e2;
    void *r1, *r2;
    while (slist_zip_iter_next(&zip, &e1, &e2) != CC_ITER_END) {
        if (strcmp((char *)e1, str_b) == 0)
            slist_zip_iter_remove(&zip, &r1, &r2);
    }

    CHECK_EQUAL_C_STRING(str_b, (char *)r1);
    CHECK_EQUAL_C_STRING(str_f, (char *)r2);
    ASSERT(0 == slist_contains(list, str_b));
    ASSERT(0 == slist_contains(list2, str_c));
    ASSERT(3 == slist_size(list));
    ASSERT(2 == slist_size(list2));

    slist_zip_iter_init(&zip, list, list2);
    while (slist_zip_iter_next(&zip, &e1, &e2) != CC_ITER_END) {
        if (strcmp((char *)e2, str_e) == 0)
            slist_zip_iter_remove(&zip, &r1, &r2);

        if (strcmp((char *)e2, str_g) == 0)
            slist_zip_iter_remove(&zip, &r1, &r2);
    }

    char *first = "";
    char *last = "";

    ASSERT(CC_ERR_VALUE_NOT_FOUND == slist_get_first(list2, (void *)&first));
    ASSERT(CC_ERR_VALUE_NOT_FOUND == slist_get_last(list2, (void *)&last));

    slist_get_first(list, (void *)&first);
    CHECK_EQUAL_C_STRING(str_d, first);

    slist_get_last(list, (void *)&last);
    CHECK_EQUAL_C_STRING(str_d, last);

    teardown_test();
    return 0;
}
