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
    int e = __nondet_int();

    slist_add(list, &a);
    slist_add(list, &b);
    slist_add(list, &b);
    slist_add(list, &c);
    slist_add(list, &d);

    __CPROVER_assert(2 == slist_contains(list, &b), "");
    __CPROVER_assert(1 == slist_contains(list, &d), "");
    __CPROVER_assert(0 == slist_contains(list, &e), "");

    teardown_test();
    return 0;
}
