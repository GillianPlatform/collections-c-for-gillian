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
    int d = __nondet_int();
    int e = __nondet_int();
    int f = __nondet_int();
    int g = __nondet_int();

    deque_add_last(deque, &a);
    deque_add_last(deque, &b);
    deque_add_last(deque, &c);
    deque_add_last(deque, &d);
    deque_add_last(deque, &e);
    deque_add_first(deque, &f);

    deque_add_at(deque, &g, 1);

    const void *const *buff = deque_get_buffer(deque);
    const int elem = *((int *)buff[0]);

    __CPROVER_assert(elem == g, "");

    const int elem1 = *((int *)buff[4]);
    __CPROVER_assert(elem1 == e, "");

    const int elem2 = *((int *)buff[6]);
    __CPROVER_assert(elem2 == f, "");

    const int elem3 = *((int *)buff[7]);
    __CPROVER_assert(elem3 == a, "");

    teardown_tests();
    return 0;
}
