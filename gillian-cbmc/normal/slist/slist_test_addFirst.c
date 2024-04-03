#include "slist.h"

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

    int a = __nondet_int();
    int b = __nondet_int();
    int c = __nondet_int();
    int d = __nondet_int();

    int prepend = __nondet_int();

    slist_add(list, &a);
    slist_add(list, &b);
    slist_add(list, &c);
    slist_add(list, &d);

    __CPROVER_assert(4 == slist_size(list), "");

    int *first;
    slist_get_first(list, (void *)&first);
    __CPROVER_assert(a == *first, "");

    slist_add_first(list, &prepend);

    __CPROVER_assert(5 == slist_size(list), "");
    slist_get_first(list, (void *)&first);
    __CPROVER_assert(prepend == *first, "");

    teardown_test();
    return 0;
}
