#include "pqueue.h"
#include <gillian-c/gillian-c.h>

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

    int aa = __builtin_annot_intval("symb_int", aa);
    int ab = __builtin_annot_intval("symb_int", ab);
    int ba = __builtin_annot_intval("symb_int", ba);
    int bb = __builtin_annot_intval("symb_int", bb);

    int a = __builtin_annot_intval("symb_int", a);
    int b = __builtin_annot_intval("symb_int", b);
    int *ptr;

    pqueue_push(p1, (void *)&b);
    pqueue_top(p1, (void *)&ptr);
    ASSERT(&b == ptr);

    pqueue_push(p1, (void *)&a);
    pqueue_top(p1, (void *)&ptr);
    ASSERT(a <= b || ptr == &a);
    ASSERT(a >= b || ptr == &b);

    struct Pair *ptr2;
    A.a = aa;
    A.b = ab;
    B.a = ba, B.b = bb;

    pqueue_push(p2, (void *)&A);
    pqueue_top(p2, (void *)&ptr2);
    ASSERT(&A == ptr2);

    pqueue_push(p2, (void *)&B);
    pqueue_top(p2, (void *)&ptr2);

    ASSERT((comp(&A, &B) <= 0) || (&A == ptr2));
    ASSERT((comp(&A, &B) >= 0) || (&B == ptr2));

    teardown_tests();
    return 0;
}
