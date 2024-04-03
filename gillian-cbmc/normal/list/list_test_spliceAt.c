#include "list.h"

static List *list1;
static List *list2;

int va, vb, vc, vd, ve, vf, vg, vh;

void setup_tests() {
    list_new(&list1), list_new(&list2);

    va = __nondet_int();
    vb = __nondet_int();
    vc = __nondet_int();
    vd = __nondet_int();
    ve = __nondet_int();
    vf = __nondet_int();
    vg = __nondet_int();
    vh = __nondet_int();

    int *a = (int *)malloc(sizeof(int));
    int *b = (int *)malloc(sizeof(int));
    int *c = (int *)malloc(sizeof(int));
    int *d = (int *)malloc(sizeof(int));

    *a = va;
    *b = vb;
    *c = vc;
    *d = vd;

    list_add(list1, a);
    list_add(list1, b);
    list_add(list1, c);
    list_add(list1, d);

    a = (int *)malloc(sizeof(int));
    b = (int *)malloc(sizeof(int));
    c = (int *)malloc(sizeof(int));
    d = (int *)malloc(sizeof(int));

    *a = ve;
    *b = vf;
    *c = vg;
    *d = vh;

    list_add(list2, a);
    list_add(list2, b);
    list_add(list2, c);
    list_add(list2, d);
}

void teardown_test() {
    list_destroy_cb(list1, free);
    list_destroy(list2);
}

int main() {
    setup_tests();

    list_splice_at(list1, list2, 2);

    __CPROVER_assert(8 == list_size(list1), "");
    __CPROVER_assert(0 == list_size(list2), "");

    int *el;
    list_get_first(list1, (void *)&el);
    __CPROVER_assert(va == *el, "");

    list_get_last(list1, (void *)&el);
    __CPROVER_assert(vd == *el, "");

    list_get_at(list1, 2, (void *)&el);
    __CPROVER_assert(ve == *el, "");

    teardown_test();
}
