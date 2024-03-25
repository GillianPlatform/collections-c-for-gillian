#include "pqueue.h"
#include <klee/klee.h> 

static struct Pair { int a, b; } A, B, C;

static int comp(const void *a, const void *b) {
    int alpha1 = ((struct Pair *)a)->a, beta1 = ((struct Pair *)a)->b;
    int alpha2 = ((struct Pair *)b)->a, beta2 = ((struct Pair *)b)->b;
    if (alpha1 != alpha2)
        return alpha1 - alpha2;
    else
        return beta1 - beta2;
}

static int comp2(const void *a, const void *b) {
    return *((int *)a) - *((int *)b);
}

static PQueue *p1, *p2;

void setup_tests() {
    pqueue_new(&p1, comp2);
    PQueueConf cfg;
    pqueue_conf_init(&cfg, comp);
    pqueue_new_conf(&cfg, &p2);
}

void teardown_tests() {
    pqueue_destroy(p1);
    pqueue_destroy(p2);
}

int main() {
    setup_tests();

    int aa; klee_make_symbolic(&aa, sizeof(int), "aa");
    int ab; klee_make_symbolic(&ab, sizeof(int), "ab");
    int ba; klee_make_symbolic(&ba, sizeof(int), "ba");
    int bb; klee_make_symbolic(&bb, sizeof(int), "bb");
    int ca; klee_make_symbolic(&ca, sizeof(int), "ca");
    int cb; klee_make_symbolic(&cb, sizeof(int), "cb");

    int a; klee_make_symbolic(&a, sizeof(int), "a");
    int b; klee_make_symbolic(&b, sizeof(int), "b");
    int c; klee_make_symbolic(&c, sizeof(int), "c");
    int *ptr;

    klee_assume(a > c && c > b);

    pqueue_push(p1, (void *)&b);
    pqueue_push(p1, (void *)&a);
    pqueue_push(p1, (void *)&c);

    pqueue_pop(p1, (void *)&ptr);
    klee_assert(&a == ptr);

    pqueue_pop(p1, (void *)&ptr);
    klee_assert(&c == ptr);

    pqueue_pop(p1, (void *)&ptr);
    klee_assert(&b == ptr);

    struct Pair *ptr2;
    A.a = aa, A.b = ab;
    B.a = ba, B.b = bb;
    C.a = ca, C.b = cb;

    klee_assume(comp(&C, &A) > 0 && comp(&A, &B) > 0);

    pqueue_push(p2, (void *)&A);
    pqueue_push(p2, (void *)&B);
    pqueue_push(p2, (void *)&C);

    pqueue_pop(p2, (void *)&ptr2);
    klee_assert(&C == ptr2);

    pqueue_pop(p2, (void *)&ptr2);
    klee_assert(&A == ptr2);

    pqueue_pop(p2, (void *)&ptr2);
    klee_assert(&B == ptr2);

    teardown_tests();
    return 0;
}
