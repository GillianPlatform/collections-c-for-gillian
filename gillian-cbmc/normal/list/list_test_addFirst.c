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
    int prepend = __nondet_int();

    list_add(list1, &a);
    list_add(list1, &b);
    list_add(list1, &c);
    list_add(list1, &d);

    __CPROVER_assert(4 == list_size(list1), "");

    int *first;
    list_get_first(list1, (void *)&first);
    __CPROVER_assert(a == *first, "");

    list_add_last(list1, &prepend);
    __CPROVER_assert(5 == list_size(list1), "");

    list_get_last(list1, (void *)&first);
    __CPROVER_assert(prepend == *first, "");

    teardown_test();
}
