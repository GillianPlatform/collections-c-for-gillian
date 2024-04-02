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

    deque_add(deque, &a);
    deque_add(deque, &b);
    deque_add(deque, &c);
    deque_add(deque, &d);
    deque_add(deque, &e);
    deque_add(deque, &f);

    __CPROVER_assume(d != a && d != b && d != c && d != e && d != f);

    DequeIter iter;
    deque_iter_init(&iter, deque);

    size_t i = 0;

    int *el;

    __CPROVER_assert(6 == deque_size(deque), "")

    while (deque_iter_next(&iter, (void *)&el) != CC_ITER_END) {
        if (*el == d)
            deque_iter_add(&iter, &g);
        if (i >= 3) {
            __CPROVER_assert(i == deque_iter_index(&iter) - 1, "")
        }
        i++;
    }
    __CPROVER_assert(7 == deque_size(deque), "")

    void *ret_;
    deque_get_at(deque, 4, &ret_);
    __CPROVER_assert(g == *(int *)ret_, "")

    teardown_tests();
    return 0;
}
