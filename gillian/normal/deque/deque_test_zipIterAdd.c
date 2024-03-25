#include "deque.h"
#include "utils.h"
#include <gillian-c/gillian-c.h>

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

    ASSUME(b != a && b != c && b != d);

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

    ASSERT(2 == index);

    deque_index_of(deque, str_i, &index);
    ASSERT(2 == index);

    deque_index_of(deque, str_c, &index);
    ASSERT(3 == index);
    ASSERT(1 == deque_contains(deque, str_h));
    ASSERT(1 == deque_contains(d2, str_i));
    ASSERT(5 == deque_size(deque));
    ASSERT(4 == deque_size(d2));
    deque_destroy(d2);

    teardown_tests();
    return 0;
}