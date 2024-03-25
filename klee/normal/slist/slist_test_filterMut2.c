#include "slist.h"
#include <klee/klee.h> 

static SList *list;
static SList *list2;
static int stat;

bool pred1(const void *e) { return *(int *)e == 0; }

bool pred2(const void *e) { return *(int *)e >= 3; }

bool pred3(const void *e) { return *(int *)e > 0; }

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

    klee_assume(!pred2(&va) && !pred2(&vb) && pred2(&vc) && pred2(&vd));

    klee_assert(4 == slist_size(list));
    slist_filter_mut(list, pred2);
    klee_assert(2 == slist_size(list));

    SListIter iter;
    int *el = NULL;
    int i = 0;
    slist_iter_init(&iter, list);
    while (slist_iter_next(&iter, (void *)&el) != CC_ITER_END) {
        if (i == 0)
            klee_assert(*el == vc);

        if (i == 1)
            klee_assert(*el == vd);

        if (i > 1)
            klee_assert(false);
        i++;
    }
    teardown_test();
    return 0;
}
