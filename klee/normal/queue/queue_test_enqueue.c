#include "queue.h"
#include <klee/klee.h> 

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

    int a; klee_make_symbolic(&a, sizeof(int), "a");
    int b; klee_make_symbolic(&b, sizeof(int), "b");
    int c; klee_make_symbolic(&c, sizeof(int), "c");

    queue_enqueue(q, &a);
    queue_enqueue(q, &b);

    klee_assert(2 == queue_size(q));

    void *p;
    queue_peek(q, &p);
    klee_assert(&a == p);

    queue_enqueue(q, &c);

    queue_peek(q, &p);
    klee_assert(&a == p);

    teardown_test();
    return 0;
}
