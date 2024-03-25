#include "slist.h"
#include <gillian-c/gillian-c.h>

static SList *list;
static SList *list2;
static int stat;

bool pred1(const void *e) { return *(int *)e == 0; }

bool pred2(const void *e) { return *(int *)e >= 3; }

bool pred3(const void *e) { return *(int *)e > 0; }

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

void CHECK_EQ_LIST(SList *l1, SList *l2) {
    ASSERT(slist_size(l1) == slist_size(l2));
    SListZipIter zip;
    slist_zip_iter_init(&zip, l1, l2);
    void *e1, *e2;
    while (slist_zip_iter_next(&zip, &e1, &e2) != CC_ITER_END) {
        ASSERT(e1 == e2);
    }
}

int main() {
    setup_test();

    ASSUME(va != 0 && vb != 0 && vc != 0 && vd != 0);

    ASSERT(4 == slist_size(list));
    slist_filter_mut(list, pred1);

    ASSERT(0 == slist_size(list));

    void *e = NULL;
    slist_get_first(list, &e);
    ASSERT(e == NULL);

    teardown_test();
    return 0;
}
