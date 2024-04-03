#include "queue.h"

static Queue *q;
static Queue *q2;
static int stat;

void setup_test() {
    stat = queue_new(&q);
    queue_new(&q2);
}

void teardown_test() {
    queue_destroy(q);
    queue_destroy(q2);
}

int main() {
    setup_test();

    int a = __nondet_int();
    int b = __nondet_int();
    int c = __nondet_int();

    queue_enqueue(q, &a);
    queue_enqueue(q, &b);

    __CPROVER_assert(2 == queue_size(q), "");

    void *p;
    queue_peek(q, &p);
    __CPROVER_assert(&a == p, "");

    queue_enqueue(q, &c);

    queue_peek(q, &p);
    __CPROVER_assert(&a == p, "");

    teardown_test();
    return 0;
}
