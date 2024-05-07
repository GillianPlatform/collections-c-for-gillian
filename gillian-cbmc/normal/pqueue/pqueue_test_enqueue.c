#include "pqueue.h"

static struct Pair {
    int a, b;
} A, B, C;

static int comp(const void *a, const void *b) {
    int aa = ((struct Pair *)a)->a, ab = ((struct Pair *)a)->b;
    int ba = ((struct Pair *)b)->a, bb = ((struct Pair *)b)->b;
    if (aa > ba || (aa == ba && ab > bb)) {
        return 1;
    } else if (aa == ba && ab == bb) {
        return 0;
    } else {

        return -1;
    };
}

static int comp2(const void *pa, const void *pb) {
    int a = *((int *)pa), b = *((int *)pb);
    if (a > b) {
        return 1;
    } else if (a == b) {
        return 0;
    } else {
        return -1;
    }
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

    int a = __nondet_int();
    int b = __nondet_int();
    int *ptr;

    pqueue_push(p1, (void *)&b);
    pqueue_top(p1, (void *)&ptr);
    __CPROVER_assert(&b == ptr, "");

    pqueue_push(p1, (void *)&a);
    pqueue_top(p1, (void *)&ptr);
    __CPROVER_assert(
        a <= b || ptr == &a,
        "if a has the highest priority, it should be at the top of the queue.");
    __CPROVER_assert(
        a >= b || ptr == &b,
        "if b has the highest priority, it should be at the top of the queue.");

    struct Pair *ptr2;
    A.a = aa;
    A.b = ab;
    B.a = ba, B.b = bb;

    pqueue_push(p2, (void *)&A);
    pqueue_top(p2, (void *)&ptr2);
    __CPROVER_assert(&A == ptr2, "");

    pqueue_push(p2, (void *)&B);
    pqueue_top(p2, (void *)&ptr2);

    __CPROVER_assert(
        (comp(&A, &B) <= 0) || (&A == ptr2),
        "If A has the highest priority, it should be at the top of the queue.");
    __CPROVER_assert((comp(&A, &B) >= 0) || (&B == ptr2),
                     "If B has the highest priority, it should be at the "
                     "top of the queue.");

    teardown_tests();
    return 0;
}
