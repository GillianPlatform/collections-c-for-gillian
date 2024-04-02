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

    deque_add_first(deque, &a);
    deque_add_first(deque, &b);
    deque_add_last(deque, &c);
    deque_add_last(deque, &d);

    int *last;
    deque_get_last(deque, (void *)&last);
    __CPROVER_assert(d == *last, "")

    int *removed;
    deque_remove_last(deque, (void *)&removed);
    __CPROVER_assert(d == *removed, "")

    deque_get_last(deque, (void *)&last);
    __CPROVER_assert(c == *last, "")

    teardown_tests();
    return 0;
}
