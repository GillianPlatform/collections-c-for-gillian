#include "slist.h"
#include <klee/klee.h> 

static SList *list;
static SList *list2;
static int stat;

int va, vb, vc, vd, ve, vf, vg, vh;

void setup_test() {
    slist_new(&list), slist_new(&list2);

    klee_make_symbolic(&va, sizeof(int), "va");
    klee_make_symbolic(&vb, sizeof(int), "vb");
    klee_make_symbolic(&vc, sizeof(int), "vc");
    klee_make_symbolic(&vd, sizeof(int), "vd");
    klee_make_symbolic(&ve, sizeof(int), "ve");
    klee_make_symbolic(&vf, sizeof(int), "vf");
    klee_make_symbolic(&vg, sizeof(int), "vg");
    klee_make_symbolic(&vh, sizeof(int), "vh");

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
    klee_make_symbolic(ins, sizeof(int), "ins");

    SListIter iter;
    slist_iter_init(&iter, list);

    klee_assume(vc != va && vc != vb && vc != vd && vd != va && vd != vb &&
           vd != *ins);

    int *el;
    while (slist_iter_next(&iter, (void *)&el) != CC_ITER_END) {
        if (*el == vc)
            slist_iter_add(&iter, ins);
    }
    klee_assert(5 == slist_size(list));

    int *li3;
    slist_get_at(list, 3, (void *)&li3);
    klee_assert(*li3 == *ins);

    int *li4;
    slist_get_at(list, 4, (void *)&li4);
    klee_assert(vd == *li4);

    int *ins2 = (int *)malloc(sizeof(int));
    klee_make_symbolic(ins2, sizeof(int), "ins2");

    slist_iter_init(&iter, list);
    while (slist_iter_next(&iter, (void *)&el) != CC_ITER_END) {
        if (*el == vd)
            slist_iter_add(&iter, ins2);
    }

    void *e;
    slist_get_last(list, &e);
    klee_assert(*ins2 == *(int *)e);
    klee_assert(6 == slist_size(list));

    teardown_test();
    return 0;
}
