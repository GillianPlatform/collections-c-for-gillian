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
    symb_str(x);
    symb_str(y);

    ASSUME(b != a && b != c && b != d);
    ASSUME(h != a && h != b && h != c && h != d);
    ASSUME(i != e && i != f && i != g);

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
            slist_zip_iter_replace(&zip, str_h, str_i, &r1, &r2);
    }

    size_t index;
    slist_index_of(list, str_h, &index);
    ASSERT(1 == index);

    slist_index_of(list, str_i, &index);
    ASSERT(1 == index);
    ASSERT(1 == slist_contains(list, str_h));
    ASSERT(1 == slist_contains(list2, str_i));

    teardown_test();
    return 0;
}
