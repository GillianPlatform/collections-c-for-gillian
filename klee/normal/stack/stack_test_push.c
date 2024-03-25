#include "stack.h"
#include <klee/klee.h> 

static Stack *s;

void setup_tests() { stack_new(&s); }

void teardown_tests() { stack_destroy(s); }

int main() {
    setup_tests();

    int a; klee_make_symbolic(&a, sizeof(int), "a");
    int b; klee_make_symbolic(&b, sizeof(int), "b");
    int c; klee_make_symbolic(&c, sizeof(int), "c");

    int *p;

    stack_push(s, (void *)&a);
    stack_peek(s, (void *)&p);
    klee_assert(&a == p);

    stack_push(s, (void *)&b);
    stack_peek(s, (void *)&p);
    klee_assert(&b == p);

    stack_push(s, (void *)&c);
    stack_peek(s, (void *)&p);
    klee_assert(&c == p);

    teardown_tests();
    return 0;
}
