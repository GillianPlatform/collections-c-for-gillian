#include "deque.h"
#include <gillian-c/gillian-c.h>

static Deque *deque;
static DequeConf conf;
int stat;

void setup_tests() { stat = deque_new(&deque); }

void teardown_tests() { deque_destroy(deque); }

bool pred1(const void *e) { return *(int *)e <= 3; }

bool pred2(const void *e) { return *(int *)e > 3; }

bool pred3(const void *e) { return *(int *)e > 5; }

int main() {
    setup_tests();

    int a = __nondet_int();
    int b = __nondet_int();
    int c = __nondet_int();
    int d = __nondet_int();
    int e = __nondet_int();
    int f = __nondet_int();

    __CPROVER_assume(pred2(&d) && pred2(&e) && pred2(&f) && !pred2(&a) && !pred2(&b) &&
           !pred2(&c));

    deque_add_last(deque, &a);
    deque_add_last(deque, &b);
    deque_add_last(deque, &c);
    deque_add_last(deque, &d);
    deque_add_last(deque, &e);
    deque_add_last(deque, &f);
    __CPROVER_assert(6 == deque_size(deque), "")

    Deque *filter = NULL;
    deque_filter(deque, pred2, &filter);
    const void *const *buff = deque_get_buffer(filter);

    __CPROVER_assert(3 == deque_size(filter), "")
    __CPROVER_assert(buff[0] == &d, "")
    __CPROVER_assert(buff[1] == &e, "")
    __CPROVER_assert(buff[2] == &f, "")

    free(filter);

    teardown_tests();
    return 0;
}
