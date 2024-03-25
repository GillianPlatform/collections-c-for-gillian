#include "slist.h"
#include <klee/klee.h> 

static SList *list;
static SList *list2;
static int stat;

void setup_test() {
    stat = slist_new(&list);
    slist_new(&list2);
};

void teardown_test() {
    slist_destroy(list);
    slist_destroy(list2);
};

int main() {
    setup_test();
    int a; klee_make_symbolic(&a, sizeof(int), "a");
    int b; klee_make_symbolic(&b, sizeof(int), "b");
    int c; klee_make_symbolic(&c, sizeof(int), "c");
    int d; klee_make_symbolic(&d, sizeof(int), "d");
    int e; klee_make_symbolic(&e, sizeof(int), "e");
    int f; klee_make_symbolic(&f, sizeof(int), "f");
    slist_add(list, &a);
    slist_add(list, &b);
    slist_add(list, &c);
    slist_add(list, &d);
    slist_add(list, &e);
    slist_add(list, &f);

    slist_reverse(list);

    int reverse_ar[] = {f, e, d, c, b, a};

    SListIter i;
    slist_iter_init(&i, list);

    void *el;
    int ind = 0;
    while (slist_iter_next(&i, &el) != CC_ITER_END) {
        klee_assert(reverse_ar[ind] == *(int *)el);
        ind++;
    }

    teardown_test();
    return 0;
}
