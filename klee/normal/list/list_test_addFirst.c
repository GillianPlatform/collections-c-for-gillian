#include "list.h"
#include <klee/klee.h> 

static List *list1;
static List *list2;

void setup_tests() { list_new(&list1), list_new(&list2); }

void teardown_test() {
    list_destroy(list1);
    list_destroy(list2);
}

int main() {
    setup_tests();

    int a; klee_make_symbolic(&a, sizeof(int), "a");
    int b; klee_make_symbolic(&b, sizeof(int), "b");
    int c; klee_make_symbolic(&c, sizeof(int), "c");
    int d; klee_make_symbolic(&d, sizeof(int), "d");
    int prepend; klee_make_symbolic(&prepend, sizeof(int), "prepend");

    list_add(list1, &a);
    list_add(list1, &b);
    list_add(list1, &c);
    list_add(list1, &d);

    klee_assert(4 == list_size(list1));

    int *first;
    list_get_first(list1, (void *)&first);
    klee_assert(a == *first);

    list_add_last(list1, &prepend);
    klee_assert(5 == list_size(list1));

    list_get_last(list1, (void *)&first);
    klee_assert(prepend == *first);

    teardown_test();
}
