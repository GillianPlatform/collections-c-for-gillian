#include "stack.h"

static Stack *s;

void setup_tests() { stack_new(&s); }

void teardown_tests() { stack_destroy(s); }

int main() {
    setup_tests();

    int a = __nondet_int();
    int b = __nondet_int();
    int c = __nondet_int();

    int *p;

    stack_push(s, (void *)&a);
    stack_peek(s, (void *)&p);
    __CPROVER_assert(&a == p, "");

    stack_push(s, (void *)&b);
    stack_peek(s, (void *)&p);
    __CPROVER_assert(&b == p, "");

    stack_push(s, (void *)&c);
    stack_peek(s, (void *)&p);
    __CPROVER_assert(&c == p, "");

    teardown_tests();
    return 0;
}
