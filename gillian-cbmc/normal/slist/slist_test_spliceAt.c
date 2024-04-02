#include "slist.h"
#include <gillian-c/gillian-c.h>

static SList *list;
static SList *list2;
static int stat;

int va, vb, vc, vd, ve, vf, vg, vh;

void setup_test() {
    slist_new(&list), slist_new(&list2);

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

    slist_add(list, a);
    slist_add(list, b);
    slist_add(list, c);
    slist_add(list, d);

    a = (int *)malloc(sizeof(int));
    b = (int *)malloc(sizeof(int));
    c = (int *)malloc(sizeof(int));
    d = (int *)malloc(sizeof(int));

    *a = ve;
    *b = vf;
    *c = vg;
    *d = vh;

    slist_add(list2, a);
    slist_add(list2, b);
    slist_add(list2, c);
    slist_add(list2, d);
};

void teardown_test() {
    slist_destroy(list);
    slist_destroy(list2);
};

int main() {
    setup_test();

    slist_splice_at(list, list2, 2);
    __CPROVER_assert(8 == slist_size(list), "")
    __CPROVER_assert(0 == slist_size(list2), "")

    int *e;
    slist_get_first(list, (void *)&e);
    __CPROVER_assert(va == *e, "")

    slist_get_last(list, (void *)&e);
    __CPROVER_assert(vd == *e, "")

    slist_get_at(list, 2, (void *)&e);
    __CPROVER_assert(ve == *e, "")

    teardown_test();
    return 0;
}
