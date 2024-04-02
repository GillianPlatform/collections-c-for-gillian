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

    deque_add_first(deque, &a);
    deque_add_last(deque, &b);
    deque_add_first(deque, &c);

    int *first;
    deque_get_first(deque, (void *)&first);

    __CPROVER_assert(c == *first, "")

    teardown_tests();
    return 0;
}
