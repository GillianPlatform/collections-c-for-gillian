#include "list.h"
#include "utils.h"
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

    char a = (char)__builtin_annot_intval("symb_int", a);

    char str_a[] = {a, '\0'};

    char b = (char)__builtin_annot_intval("symb_int", b);

    char str_b[] = {b, '\0'};

    char c = (char)__builtin_annot_intval("symb_int", c);

    char str_c[] = {c, '\0'};

    char d = (char)__builtin_annot_intval("symb_int", d);

    char str_d[] = {d, '\0'};

    char e = (char)__builtin_annot_intval("symb_int", e);

    char str_e[] = {e, '\0'};

    char f = (char)__builtin_annot_intval("symb_int", f);

    char str_f[] = {f, '\0'};

    char g = (char)__builtin_annot_intval("symb_int", g);

    char str_g[] = {g, '\0'};

    char h = (char)__builtin_annot_intval("symb_int", h);

    char str_h[] = {h, '\0'};

    char i = (char)__builtin_annot_intval("symb_int", i);

    char str_i[] = {i, '\0'};

    ASSUME(a != b && a != c && a != d && a != h && b != c && b != d && b != h &&
           c != d && c != h && d != h);

    ASSUME(e != f && e != g && e != i && f != g && f != i && g != i);

    list_add(list1, str_a);
    list_add(list1, str_b);
    list_add(list1, str_c);
    list_add(list1, str_d);

    list_add(list2, str_e);
    list_add(list2, str_f);
    list_add(list2, str_g);

    ListZipIter zip;
    list_zip_iter_init(&zip, list1, list2);

    void *e1, *e2;
    void *r1, *r2;
    while (list_zip_iter_next(&zip, &e1, &e2) != CC_ITER_END) {
        if (strcmp((char *)e1, str_b) == 0)
            list_zip_iter_replace(&zip, str_h, str_i, &r1, &r2);
    }

    size_t index;
    ASSERT(CC_OK == list_index_of(list1, str_h, zero_if_ptr_eq, &index));
    ASSERT(1 == index);

    ASSERT(CC_OK == list_index_of(list2, str_i, zero_if_ptr_eq, &index));
    ASSERT(1 == index);
    ASSERT(1 == list_contains(list1, str_h));
    ASSERT(1 == list_contains(list2, str_i));

    teardown_test();
}
