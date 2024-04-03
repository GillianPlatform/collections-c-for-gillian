#include "pqueue.h"

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

    int aa = __nondet_int();
    int ab = __nondet_int();
    int ba = __nondet_int();
    int bb = __nondet_int();
    int ca = __nondet_int();
    int cb = __nondet_int();

    int a = __nondet_int();
    int b = __nondet_int();
    int c = __nondet_int();
    int *ptr;

    __CPROVER_assume(a > c && c > b);

    pqueue_push(p1, (void *)&b);
    pqueue_push(p1, (void *)&a);
    pqueue_push(p1, (void *)&c);

    pqueue_pop(p1, (void *)&ptr);
    __CPROVER_assert(&a == ptr, "");

    pqueue_pop(p1, (void *)&ptr);
    __CPROVER_assert(&c == ptr, "");

    pqueue_pop(p1, (void *)&ptr);
    __CPROVER_assert(&b == ptr, "");

    struct Pair *ptr2;
    A.a = aa, A.b = ab;
    B.a = ba, B.b = bb;
    C.a = ca, C.b = cb;

    __CPROVER_assume(comp(&C, &A) > 0 && comp(&A, &B) > 0);

    pqueue_push(p2, (void *)&A);
    pqueue_push(p2, (void *)&B);
    pqueue_push(p2, (void *)&C);

    pqueue_pop(p2, (void *)&ptr2);
    __CPROVER_assert(&C == ptr2, "");

    pqueue_pop(p2, (void *)&ptr2);
    __CPROVER_assert(&A == ptr2, "");

    pqueue_pop(p2, (void *)&ptr2);
    __CPROVER_assert(&B == ptr2, "");

    teardown_tests();
    return 0;
}
