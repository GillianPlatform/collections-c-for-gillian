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

    int append; klee_make_symbolic(&append, sizeof(int), "append");

    slist_add(list, &a);
    slist_add(list, &b);
    slist_add(list, &c);
    slist_add(list, &d);

    klee_assert(4 == slist_size(list));

    int *last;
    slist_get_last(list, (void *)&last);
    klee_assert(d == *last);

    slist_add_last(list, &append);
    klee_assert(5 == slist_size(list));

    slist_get_last(list, (void *)&last);
    klee_assert(append == *last);

    teardown_test();
    return 0;
}
