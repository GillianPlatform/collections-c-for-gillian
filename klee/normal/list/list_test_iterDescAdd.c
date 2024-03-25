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

    int *a = (int *)malloc(sizeof(int));
    int *b = (int *)malloc(sizeof(int));
    klee_make_symbolic(a, sizeof(int), "a");
    ;
    klee_make_symbolic(b, sizeof(int), "b");

    klee_assume(vc != va && vc != vb && vc != vd && vd != va && vd != vb);

    ListIter iter;
    list_diter_init(&iter, list1);

    int *i;
    while (list_diter_next(&iter, (void *)&i) != CC_ITER_END) {
        if (*i == vd) // add to tail
            list_diter_add(&iter, a);

        if (*i == vc)
            list_diter_add(&iter, b);
    }

    klee_assert(6 == list_size(list1));
    int *el;
    list_get_first(list1, (void *)&el);
    klee_assert(va == *el);

    list_get_last(list1, (void *)&el);
    klee_assert(vd == *el);

    list_get_at(list1, 2, (void *)&el);
    klee_assert(*b == *el);

    list_get_at(list1, 4, (void *)&el);
    klee_assert(*a == *el);

    teardown_test();
}
