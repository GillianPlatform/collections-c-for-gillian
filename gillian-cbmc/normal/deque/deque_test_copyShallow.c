#include "deque.h"

static Deque *deque;
static DequeConf conf;
int stat;

void setup_tests() { stat = deque_new(&deque); }

void teardown_tests() { deque_destroy(deque); }

int main() {
    setup_tests();

    int a = __nondet_int();
    int b = __nondet_int();
    int c = __nondet_int();

    deque_add_last(deque, &a);
    deque_add_last(deque, &b);
    deque_add_last(deque, &c);

    Deque *copy;
    deque_copy_shallow(deque, &copy);

    int size = deque_size(copy);
    __CPROVER_assert(3 == size, "");

    int *ca;
    deque_get_at(copy, 0, (void *)&ca);

    int *cb;
    deque_get_at(copy, 1, (void *)&cb);

    int *cc;
    deque_get_at(copy, 2, (void *)&cc);

    __CPROVER_assert(a == *ca, "");
    __CPROVER_assert(b == *cb, "");
    __CPROVER_assert(c == *cc, "");
    deque_destroy(copy);

    teardown_tests();
    return 0;
}
