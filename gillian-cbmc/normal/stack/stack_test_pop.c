#include "stack.h"
#include <gillian-c/gillian-c.h>

static Stack *s;

void setup_tests() { stack_new(&s); }

void teardown_tests() { stack_destroy(s); }

int main() {
    setup_tests();

    int a = __nondet_int();
    int b = __nondet_int();
    int c = __nondet_int();

    stack_push(s, (void *)&a);
    stack_push(s, (void *)&b);
    stack_push(s, (void *)&c);

    int *pop;
    int *peek;

    stack_pop(s, (void *)&pop);
    __CPROVER_assert(&c == pop, "")

    stack_peek(s, (void *)&peek);
    __CPROVER_assert(&b == peek, "")

    teardown_tests();
    return 0;
}
