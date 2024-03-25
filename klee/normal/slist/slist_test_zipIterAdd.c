#include "slist.h"
#include "utils.h"
#include <klee/klee.h> 

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

    klee_assume(b != a && b != c && b != d);
    klee_assume(h != a && h != b && h != c && h != d);
    klee_assume(c != a && c != d);
    klee_assume(i != e && i != f && i != g);

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
    while (slist_zip_iter_next(&zip, &e1, &e2) != CC_ITER_END) {
        if (strcmp((char *)e1, str_b) == 0)
            slist_zip_iter_add(&zip, str_h, str_i);
    }

    size_t index;
    slist_index_of(list, str_h, &index);
    klee_assert(2 == index);

    slist_index_of(list2, str_i, &index);
    klee_assert(2 == index);

    slist_index_of(list, str_c, &index);
    klee_assert(3 == index);

    klee_assert(1 == slist_contains(list, str_h));
    klee_assert(1 == slist_contains(list2, str_i));
    klee_assert(5 == slist_size(list));
    klee_assert(4 == slist_size(list2));

    slist_zip_iter_init(&zip, list, list2);
    while (slist_zip_iter_next(&zip, &e1, &e2) != CC_ITER_END) {
        if (strcmp((char *)e2, str_g) == 0)
            slist_zip_iter_add(&zip, str_x, str_y);
    }

    char *last;
    slist_get_last(list2, (void *)&last);
    klee_assert(str_y == last);

    slist_get_last(list, (void *)&last);
    klee_assert(str_d == last);

    teardown_test();
    return 0;
}
