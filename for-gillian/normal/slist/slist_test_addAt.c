#include "slist.h"
#include <gillian-c/gillian-c.h>

static SList *list;
static SList *list2;
static int stat;

int va, vb, vc, vd, ve, vf, vg, vh;

void setup_test() {
    slist_new(&list), slist_new(&list2);

    va = __builtin_annot_intval("symb_int", va);
    vb = __builtin_annot_intval("symb_int", vb);
    vc = __builtin_annot_intval("symb_int", vc);
    vd = __builtin_annot_intval("symb_int", vd);
    ve = __builtin_annot_intval("symb_int", ve);
    vf = __builtin_annot_intval("symb_int", vf);
    vg = __builtin_annot_intval("symb_int", vg);
    vh = __builtin_annot_intval("symb_int", vh);

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

    int *ins = (int *)malloc(sizeof(int));
    *ins = __builtin_annot_intval("symb_int", *ins);

    slist_add_at(list, ins, 2);
    ASSERT(5 == slist_size(list));

    int *new;
    slist_get_at(list, 2, (void *)&new);
    ASSERT(*ins == *new);
    ASSERT(CC_OK == slist_add_at(list, ins, 4));
    ASSERT(CC_OK == slist_add_at(list, ins, 0));

    void *el;
    slist_get_first(list, &el);
    ASSERT(*ins == *((int *)el));

    slist_get_first(list, &el);
    ASSERT(*ins == *((int *)el));

    teardown_test();
    return 0;
}
