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

    char s1; klee_make_symbolic(&s1, sizeof(char), "s1");

    char str_s1[] = {s1, '\0'};

    char s2; klee_make_symbolic(&s2, sizeof(char), "s2");

    char str_s2[] = {s2, '\0'};

    char s3; klee_make_symbolic(&s3, sizeof(char), "s3");

    char str_s3[] = {s3, '\0'};

    char s4; klee_make_symbolic(&s4, sizeof(char), "s4");

    char str_s4[] = {s4, '\0'};

    klee_assert(CC_OK == slist_add(list, str_s1));
    klee_assert(CC_OK == slist_add(list, str_s2));
    klee_assert(CC_OK == slist_add(list, str_s3));
    klee_assert(CC_OK == slist_add(list, str_s4));

    void *e;
    slist_get_first(list, &e);
    klee_assert(e != NULL);

    slist_get_last(list, &e);
    klee_assert(e != NULL);

    teardown_test();
    return 0;
}
