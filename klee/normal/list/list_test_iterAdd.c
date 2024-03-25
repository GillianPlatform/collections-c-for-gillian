#include "list.h"
#include <klee/klee.h> 

static List *list1;
static List *list2;

int va, vb, vc, vd, ve, vf, vg, vh;

void setup_tests() {
    list_new(&list1), list_new(&list2);

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

    int ins_v1; klee_make_symbolic(&ins_v1, sizeof(int), "ins_v1");
    int *ins = (int *)malloc(sizeof(int));
    *ins = ins_v1;

    klee_assume(ins_v1 != vd);

    ListIter iter;
    list_iter_init(&iter, list1);

    klee_assume(vc != va && vc != vb && vc != vd && vd != va && vd != vb);

    int *el;
    while (list_iter_next(&iter, (void *)&el) != CC_ITER_END) {
        if (*el == vc)
            list_iter_add(&iter, ins);
    }

    klee_assert(5 == list_size(list1));

    int *li3;
    list_get_at(list1, 3, (void *)&li3);

    klee_assert(*li3 == *ins);

    int *li4;
    list_get_at(list1, 4, (void *)&li4);
    klee_assert(vd == *li4);

    list_iter_init(&iter, list1);

    int ins_v2; klee_make_symbolic(&ins_v2, sizeof(int), "ins_v2");
    ins = (int *)malloc(sizeof(int));
    *ins = ins_v2;

    while (list_iter_next(&iter, (void *)&el) != CC_ITER_END) {
        if (*el == vd) {
            list_iter_add(&iter, ins);
        }
    }

    void *e;
    list_get_last(list1, &e);
    klee_assert(*ins == *((int *)e));

    teardown_test();
}
