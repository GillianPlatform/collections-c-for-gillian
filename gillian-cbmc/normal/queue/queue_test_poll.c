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
    queue_enqueue(q, &c);

    void *p;

    queue_poll(q, &p);
    __CPROVER_assert(&a == p, "");

    queue_peek(q, &p);
    __CPROVER_assert(&b == p, "");

    queue_poll(q, &p);
    __CPROVER_assert(&b == p, "");

    queue_peek(q, &p);
    __CPROVER_assert(&c == p, "");

    teardown_test();
    return 0;
}
