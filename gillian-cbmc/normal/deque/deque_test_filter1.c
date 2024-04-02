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

    __CPROVER_assume(!pred1(&d) && !pred1(&e) && !pred1(&f) && pred1(&a) && pred1(&b) &&
           pred1(&c));

    deque_add_last(deque, &a);
    deque_add_last(deque, &b);
    deque_add_last(deque, &c);
    deque_add_last(deque, &d);
    deque_add_last(deque, &e);
    deque_add_last(deque, &f);
    __CPROVER_assert(6 == deque_size(deque), "")

    Deque *filter = NULL;
    deque_filter(deque, pred1, &filter);
    __CPROVER_assert(3 == deque_size(filter), "")
    const void *const *buff = deque_get_buffer(filter);

    __CPROVER_assert(buff[0] == &a, "")
    __CPROVER_assert(buff[1] == &b, "")

    const void *elem = buff[2];
    __CPROVER_assert(elem == &c, "")
    free(filter);

    teardown_tests();
    return 0;
}
