#include "deque.h"
#include <klee/klee.h> 

static Deque *deque;
static DequeConf conf;
int stat;

void setup_tests() { stat = deque_new(&deque); }

void teardown_tests() { deque_destroy(deque); }

int main() {
    setup_tests();

    int a; klee_make_symbolic(&a, sizeof(int), "a");
    int b; klee_make_symbolic(&b, sizeof(int), "b");
    int c; klee_make_symbolic(&c, sizeof(int), "c");
    int d; klee_make_symbolic(&d, sizeof(int), "d");
    int e; klee_make_symbolic(&e, sizeof(int), "e");
    int f; klee_make_symbolic(&f, sizeof(int), "f");
    int g; klee_make_symbolic(&g, sizeof(int), "g");

    deque_add_last(deque, &a);
    deque_add_first(deque, &b);
    deque_add_first(deque, &c);
    deque_add_first(deque, &d);
    deque_add_first(deque, &e);
    deque_add_first(deque, &f);

    deque_add_at(deque, &g, 3);

    const void *const *buff = deque_get_buffer(deque);

    const void *elem = buff[6];
    klee_assert(elem == &g);

    const void *elem1 = buff[0];
    klee_assert(elem1 == &b);

    const void *elem2 = buff[7];
    klee_assert(elem2 == &c);

    const void *elem3 = buff[1];
    klee_assert(elem3 == &a);

    teardown_tests();
    return 0;
}
