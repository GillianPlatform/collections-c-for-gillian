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
    int e; klee_make_symbolic(&e, sizeof(int), "e");

    klee_assume(a != b && a != c && a != d && a != e && b != c && b != d && b != e &&
           c != d && c != e && d != e);

    list_add(list1, &a);
    list_add(list1, &b);
    list_add(list1, &b);
    list_add(list1, &c);
    list_add(list1, &d);

    klee_assert(2 == list_contains(list1, &b));
    klee_assert(1 == list_contains(list1, &d));
    klee_assert(0 == list_contains(list1, &e));

    teardown_test();
}
