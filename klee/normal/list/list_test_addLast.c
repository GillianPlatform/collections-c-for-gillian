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
    int append; klee_make_symbolic(&append, sizeof(int), "append");

    list_add(list1, &a);
    list_add(list1, &b);
    list_add(list1, &c);
    list_add(list1, &d);

    klee_assert(4 == list_size(list1));

    int *last;
    list_get_last(list1, (void *)&last);
    klee_assert(d == *last);

    list_add_last(list1, &append);
    klee_assert(5 == list_size(list1));

    list_get_last(list1, (void *)&last);
    klee_assert(append == *last);

    teardown_test();
}
