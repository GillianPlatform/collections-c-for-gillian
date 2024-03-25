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

    int a; klee_make_symbolic(&a, sizeof(int), "a");
    int b; klee_make_symbolic(&b, sizeof(int), "b");
    int *ptr;

    pqueue_push(p1, (void *)&b);
    pqueue_top(p1, (void *)&ptr);
    klee_assert(&b == ptr);

    pqueue_push(p1, (void *)&a);
    pqueue_top(p1, (void *)&ptr);
    klee_assert(((a > b) && (&a == ptr)) || ((a <= b) && (&b == ptr)));

    struct Pair *ptr2;
    A.a = aa;
    A.b = ab;
    B.a = ba, B.b = bb;

    pqueue_push(p2, (void *)&A);
    pqueue_top(p2, (void *)&ptr2);
    klee_assert(&A == ptr2);

    pqueue_push(p2, (void *)&B);
    pqueue_top(p2, (void *)&ptr2);

    klee_assert(((comp(&A, &B) >= 0) && (&A == ptr2)) ||
           ((comp(&A, &B) < 0) && (&B == ptr2)));

    teardown_tests();
    return 0;
}
