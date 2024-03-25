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

    SListIter iter;
    slist_iter_init(&iter, list);

    ASSUME(vc != va && vc != vb && vc != vd && vd != va && vd != vb &&
           vd != *ins);

    int *el;
    while (slist_iter_next(&iter, (void *)&el) != CC_ITER_END) {
        if (*el == vc)
            slist_iter_add(&iter, ins);
    }
    ASSERT(5 == slist_size(list));

    int *li3;
    slist_get_at(list, 3, (void *)&li3);
    ASSERT(*li3 == *ins);

    int *li4;
    slist_get_at(list, 4, (void *)&li4);
    ASSERT(vd == *li4);

    int *ins2 = (int *)malloc(sizeof(int));
    *ins2 = __builtin_annot_intval("symb_int", *ins2);

    slist_iter_init(&iter, list);
    while (slist_iter_next(&iter, (void *)&el) != CC_ITER_END) {
        if (*el == vd)
            slist_iter_add(&iter, ins2);
    }

    void *e;
    slist_get_last(list, &e);
    ASSERT(*ins2 == *(int *)e);
    ASSERT(6 == slist_size(list));

    teardown_test();
    return 0;
}
