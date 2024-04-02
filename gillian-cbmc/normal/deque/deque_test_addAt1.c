#include "deque.h"
#include <gillian-c/gillian-c.h>

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
    deque_add_last(deque, &f);

    deque_add_at(deque, &g, 4);

    const void *const *buff = deque_get_buffer(deque);

    __CPROVER_assert(buff[4] == &g, "")

    __CPROVER_assert(buff[5] == &e, "")

    const void *elem = buff[6];
    __CPROVER_assert(elem == &f, "")

    teardown_tests();
    return 0;
}
