#include "list.h"
#include "utils.h"
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

    char a; klee_make_symbolic(&a, sizeof(char), "a");

    char str_a[] = {a, '\0'};

    char b; klee_make_symbolic(&b, sizeof(char), "b");

    char str_b[] = {b, '\0'};

    char c; klee_make_symbolic(&c, sizeof(char), "c");

    char str_c[] = {c, '\0'};

    char d; klee_make_symbolic(&d, sizeof(char), "d");

    char str_d[] = {d, '\0'};

    char e; klee_make_symbolic(&e, sizeof(char), "e");

    char str_e[] = {e, '\0'};

    char f; klee_make_symbolic(&f, sizeof(char), "f");

    char str_f[] = {f, '\0'};

    char g; klee_make_symbolic(&g, sizeof(char), "g");

    char str_g[] = {g, '\0'};

    char h; klee_make_symbolic(&h, sizeof(char), "h");

    char str_h[] = {h, '\0'};

    char i; klee_make_symbolic(&i, sizeof(char), "i");

    char str_i[] = {i, '\0'};

    char x; klee_make_symbolic(&x, sizeof(char), "x");

    char str_x[] = {x, '\0'};

    char y; klee_make_symbolic(&y, sizeof(char), "y");

    char str_y[] = {y, '\0'};

    klee_assume(a != b && a != c && a != d && a != h && a != x);
    klee_assume(b != c && b != d && b != h && b != x);
    klee_assume(c != d && c != h && c != x);
    klee_assume(d != h && d != x && h != x);

    klee_assume(e != f && e != g && e != i && e != y && f != g && f != i && f != y &&
           g != i && g != y && i != y);

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
    while (list_zip_iter_next(&zip, &e1, &e2) != CC_ITER_END) {
        if (strcmp((char *)e1, str_b) == 0)
            list_zip_iter_add(&zip, str_h, str_i);
    }

    size_t index;
    klee_assert(CC_OK == list_index_of(list1, str_h, zero_if_ptr_eq, &index));
    klee_assert(2 == index);

    klee_assert(CC_OK == list_index_of(list1, str_i, zero_if_ptr_eq, &index));
    klee_assert(2 == index);

    klee_assert(CC_OK == list_index_of(list1, str_c, zero_if_ptr_eq, &index));
    klee_assert(3 == index);

    klee_assert(1 == list_contains(list1, str_h));
    klee_assert(1 == list_contains(list2, str_i));
    klee_assert(5 == list_size(list1));
    klee_assert(4 == list_size(list2));

    list_zip_iter_init(&zip, list1, list2);
    while (list_zip_iter_next(&zip, &e1, &e2) != CC_ITER_END) {
        if (strcmp((char *)e2, str_g) == 0)
            list_zip_iter_add(&zip, str_x, str_y);
    }

    char *last;
    list_get_last(list1, (void *)&last);
    CHECK_EQUAL_C_STRING(str_d, last);

    list_get_last(list2, (void *)&last);
    CHECK_EQUAL_C_STRING(str_y, last);

    teardown_test();
}
