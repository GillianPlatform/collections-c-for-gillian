#include "deque.h"

static Deque *deque;
static DequeConf conf;
int stat;

void setup_tests() { stat = deque_new(&deque); }

void teardown_tests() { deque_destroy(deque); }

int main() {
    setup_tests();

    DequeConf conf;
    deque_conf_init(&conf);

    conf.capacity = 2;

    Deque *deque;
    deque_new_conf(&conf, &deque);

    __CPROVER_assert(2 == deque_capacity(deque), "");

    int a = __nondet_int();
    int b = __nondet_int();
    int c = __nondet_int();

    deque_add(deque, &a);
    deque_add(deque, &b);
    deque_add(deque, &c);

    __CPROVER_assert(4 == deque_capacity(deque), "");

    teardown_tests();
    return 0;
}
