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

    deque_add_first(deque, &a);
    deque_add_first(deque, &b);
    deque_add_first(deque, &c);

    klee_assert(3 == deque_size(deque));

    size_t m = deque_capacity(deque);
    const void *const *u = deque_get_buffer(deque);
    const void *e = u[m - 1];

    klee_assert(e == &a);

    e = u[m - 2];
    klee_assert(e == &b);

    e = u[m - 3];
    klee_assert(e == &c);

    teardown_tests();
    return 0;
}
