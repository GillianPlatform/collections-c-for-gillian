#include "list.h"

static List *list1;
static List *list2;

void setup_tests() { list_new(&list1), list_new(&list2); }

void teardown_test() {
    list_destroy(list1);
    list_destroy(list2);
}

int main() {
    setup_tests();

    int a = __nondet_int();
    int b = __nondet_int();
    int c = __nondet_int();
    int d = __nondet_int();
    int append = __nondet_int();

    list_add(list1, &a);
    list_add(list1, &b);
    list_add(list1, &c);
    list_add(list1, &d);

    __CPROVER_assert(4 == list_size(list1), "");

    int *last;
    list_get_last(list1, (void *)&last);
    __CPROVER_assert(d == *last, "");

    list_add_last(list1, &append);
    __CPROVER_assert(5 == list_size(list1), "");

    list_get_last(list1, (void *)&last);
    __CPROVER_assert(append == *last, "");

    teardown_test();
}
