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
    deque_add_first(deque, &c);
    deque_add_first(deque, &d);
    deque_add_first(deque, &e);
    deque_add_first(deque, &f);

    deque_add_at(deque, &g, 1);

    const void *const *buff = deque_get_buffer(deque);
    const void *elem = buff[5];

    __CPROVER_assert(elem == &g, "")

    const void *elem1 = buff[0];
    __CPROVER_assert(elem1 == &a, "")

    const void *elem2 = buff[7];
    __CPROVER_assert(elem2 == &c, "")

    const void *elem3 = buff[3];
    __CPROVER_assert(elem3 == &f, "")

    teardown_tests();
    return 0;
}
