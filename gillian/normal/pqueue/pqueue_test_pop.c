#include "pqueue.h"
#include <gillian-c/gillian-c.h>

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

    int aa = __builtin_annot_intval("symb_int", aa);
    int ab = __builtin_annot_intval("symb_int", ab);
    int ba = __builtin_annot_intval("symb_int", ba);
    int bb = __builtin_annot_intval("symb_int", bb);
    int ca = __builtin_annot_intval("symb_int", ca);
    int cb = __builtin_annot_intval("symb_int", cb);

    int a = __builtin_annot_intval("symb_int", a);
    int b = __builtin_annot_intval("symb_int", b);
    int c = __builtin_annot_intval("symb_int", c);
    int *ptr;

    ASSUME(a > c && c > b);

    pqueue_push(p1, (void *)&b);
    pqueue_push(p1, (void *)&a);
    pqueue_push(p1, (void *)&c);

    pqueue_pop(p1, (void *)&ptr);
    ASSERT(&a == ptr);

    pqueue_pop(p1, (void *)&ptr);
    ASSERT(&c == ptr);

    pqueue_pop(p1, (void *)&ptr);
    ASSERT(&b == ptr);

    struct Pair *ptr2;
    A.a = aa, A.b = ab;
    B.a = ba, B.b = bb;
    C.a = ca, C.b = cb;

    ASSUME(comp(&C, &A) > 0 && comp(&A, &B) > 0);

    pqueue_push(p2, (void *)&A);
    pqueue_push(p2, (void *)&B);
    pqueue_push(p2, (void *)&C);

    pqueue_pop(p2, (void *)&ptr2);
    ASSERT(&C == ptr2);

    pqueue_pop(p2, (void *)&ptr2);
    ASSERT(&A == ptr2);

    pqueue_pop(p2, (void *)&ptr2);
    ASSERT(&B == ptr2);

    teardown_tests();
    return 0;
}
