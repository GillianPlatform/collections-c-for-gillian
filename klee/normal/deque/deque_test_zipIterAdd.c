#include "deque.h"
#include "utils.h"
#include <klee/klee.h> 

static Deque *deque;
static DequeConf conf;
int stat;

void setup_tests() { stat = deque_new(&deque); }

void teardown_tests() { deque_destroy(deque); }

int main() {
    setup_tests();

    symb_str(a);
    symb_str(b);
    symb_str(c);
    symb_str(d);
    symb_str(e);
    symb_str(f);
    symb_str(g);

    klee_assume(b != a && b != c && b != d);

    deque_add(deque, str_a);
    deque_add(deque, str_b);
    deque_add(deque, str_c);
    deque_add(deque, str_d);

    Deque *d2;
    deque_new(&d2);

    deque_add(d2, str_e);
    deque_add(d2, str_f);
    deque_add(d2, str_g);

    symb_str(h);
    symb_str(i);

    DequeZipIter zip;
    deque_zip_iter_init(&zip, deque, d2);

    void *e1, *e2;
    while (deque_zip_iter_next(&zip, &e1, &e2) != CC_ITER_END) {
        if (strcmp((char *)e1, str_b) == 0)
            deque_zip_iter_add(&zip, str_h, str_i);
    }

    size_t index;
    deque_index_of(deque, str_h, &index);

    klee_assert(2 == index);

    deque_index_of(deque, str_i, &index);
    klee_assert(2 == index);

    deque_index_of(deque, str_c, &index);
    klee_assert(3 == index);
    klee_assert(1 == deque_contains(deque, str_h));
    klee_assert(1 == deque_contains(d2, str_i));
    klee_assert(5 == deque_size(deque));
    klee_assert(4 == deque_size(d2));
    deque_destroy(d2);

    teardown_tests();
    return 0;
}
