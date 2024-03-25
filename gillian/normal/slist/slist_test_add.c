#include "slist.h"
#include <gillian-c/gillian-c.h>

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

    char s1 = (char)__builtin_annot_intval("symb_int", s1);

    char str_s1[] = {s1, '\0'};

    char s2 = (char)__builtin_annot_intval("symb_int", s2);

    char str_s2[] = {s2, '\0'};

    char s3 = (char)__builtin_annot_intval("symb_int", s3);

    char str_s3[] = {s3, '\0'};

    char s4 = (char)__builtin_annot_intval("symb_int", s4);

    char str_s4[] = {s4, '\0'};

    ASSERT(CC_OK == slist_add(list, str_s1));
    ASSERT(CC_OK == slist_add(list, str_s2));
    ASSERT(CC_OK == slist_add(list, str_s3));
    ASSERT(CC_OK == slist_add(list, str_s4));

    void *e;
    slist_get_first(list, &e);
    ASSERT(e != NULL);

    slist_get_last(list, &e);
    ASSERT(e != NULL);

    teardown_test();
    return 0;
}
