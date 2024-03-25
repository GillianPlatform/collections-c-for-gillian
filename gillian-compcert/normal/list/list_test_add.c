#include "list.h"
#include <gillian-c/gillian-c.h>

static List *list1;
static List *list2;

void setup_tests() { list_new(&list1), list_new(&list2); }

void teardown_test() {
    list_destroy(list1);
    list_destroy(list2);
}

int main() {
    setup_tests();

    char s1 = (char)__builtin_annot_intval("symb_int", s1);

    char str_s1[] = {s1, '\0'};

    char s2 = (char)__builtin_annot_intval("symb_int", s2);

    char str_s2[] = {s2, '\0'};

    char s3 = (char)__builtin_annot_intval("symb_int", s3);

    char str_s3[] = {s3, '\0'};

    char s4 = (char)__builtin_annot_intval("symb_int", s4);

    char str_s4[] = {s4, '\0'};

    ASSERT(CC_OK == list_add(list1, str_s1));
    ASSERT(CC_OK == list_add(list1, str_s2));
    ASSERT(CC_OK == list_add(list1, str_s3));
    ASSERT(CC_OK == list_add(list1, str_s4));

    void *e;
    list_get_first(list1, &e);
    ASSERT(e != NULL);

    list_get_last(list1, &e);
    ASSERT(e != NULL);

    teardown_test();
}
