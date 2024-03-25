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

    deque_add(deque, &a);
    deque_add(deque, &b);
    deque_add(deque, &c);
    deque_add(deque, &d);
    deque_add(deque, &e);
    deque_add(deque, &f);

    klee_assume(d != a && d != b && d != c && d != e && d != f);

    DequeIter iter;
    deque_iter_init(&iter, deque);

    size_t i = 0;
    void *el;
    while (deque_iter_next(&iter, &el) != CC_ITER_END) {
        if (i == 3)
            deque_iter_remove(&iter, NULL);

        if (i > 2) {
            klee_assert(5 == deque_size(deque));
        } else {
            klee_assert(6 == deque_size(deque));
        }
        if (i >= 3) {
            klee_assert(i - 1 == deque_iter_index(&iter));
        }
        i++;
    }

    teardown_tests();
    return 0;
}
