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

    deque_add_last(deque, &a);
    deque_add_last(deque, &b);
    deque_add_last(deque, &c);

    Deque *copy;
    deque_copy_shallow(deque, &copy);

    int size = deque_size(copy);
    klee_assert(3 == size);

    int *ca;
    deque_get_at(copy, 0, (void *)&ca);

    int *cb;
    deque_get_at(copy, 1, (void *)&cb);

    int *cc;
    deque_get_at(copy, 2, (void *)&cc);

    klee_assert(a == *ca);
    klee_assert(b == *cb);
    klee_assert(c == *cc);
    deque_destroy(copy);

    teardown_tests();
    return 0;
}
