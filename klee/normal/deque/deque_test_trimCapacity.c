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

    klee_assert(8 == deque_capacity(deque));

    deque_trim_capacity(deque);

    klee_assert(4 == deque_capacity(deque));

    teardown_tests();
    return 0;
}
