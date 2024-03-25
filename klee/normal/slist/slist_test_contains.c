#include "slist.h"
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

    int a; klee_make_symbolic(&a, sizeof(int), "a");
    int b; klee_make_symbolic(&b, sizeof(int), "b");
    int c; klee_make_symbolic(&c, sizeof(int), "c");
    int d; klee_make_symbolic(&d, sizeof(int), "d");
    int e; klee_make_symbolic(&e, sizeof(int), "e");

    slist_add(list, &a);
    slist_add(list, &b);
    slist_add(list, &b);
    slist_add(list, &c);
    slist_add(list, &d);

    klee_assert(2 == slist_contains(list, &b));
    klee_assert(1 == slist_contains(list, &d));
    klee_assert(0 == slist_contains(list, &e));

    teardown_test();
    return 0;
}
