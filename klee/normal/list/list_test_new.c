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

    klee_assert(list1 != NULL);
    klee_assert(list2 != NULL);

    void *e = NULL;
    list_get_first(list1, &e);
    klee_assert(e == NULL);

    list_get_last(list1, &e);
    klee_assert(e == NULL);

    klee_assert(0 == list_size(list1));
    klee_assert(list1 != list2);

    teardown_test();
}
