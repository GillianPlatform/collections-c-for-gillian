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
    int d; klee_make_symbolic(&d, sizeof(int), "d");

    deque_add_first(deque, &a);
    deque_add_last(deque, &b);
    deque_add_last(deque, &c);
    deque_add_last(deque, &d);

    int *first;
    deque_get_first(deque, (void *)&first);
    klee_assert(a == *first);

    int *removed;
    deque_remove_first(deque, (void *)&removed);
    klee_assert(a == *removed);

    deque_get_first(deque, (void *)&first);
    klee_assert(b == *first);

    teardown_tests();
    return 0;
}
