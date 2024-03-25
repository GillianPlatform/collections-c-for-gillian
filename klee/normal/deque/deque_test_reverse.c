#include "deque.h"
#include <klee/klee.h> 

static Deque *deque;
static DequeConf conf;
int stat;

void setup_tests() { stat = deque_new(&deque); }

void teardown_tests() { deque_destroy(deque); }

int main() {
    setup_tests();

    int a; klee_make_symbolic(&a, sizeof(int), "a");
    int b; klee_make_symbolic(&b, sizeof(int), "b");
    int c; klee_make_symbolic(&c, sizeof(int), "c");

    deque_add(deque, &a);
    deque_add(deque, &b);
    deque_add(deque, &c);

    deque_reverse(deque);

    int *ra;
    deque_get_at(deque, 0, (void *)&ra);
    int *rb;
    deque_get_at(deque, 1, (void *)&rb);
    int *rc;
    deque_get_at(deque, 2, (void *)&rc);

    klee_assert(c == *ra);
    klee_assert(b == *rb);
    klee_assert(a == *rc);

    teardown_tests();
    return 0;
}
