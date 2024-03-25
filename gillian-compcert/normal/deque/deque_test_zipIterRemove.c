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

    DequeZipIter zip;
    deque_zip_iter_init(&zip, deque, d2);

    void *e1, *e2;
    void *r1, *r2;
    while (deque_zip_iter_next(&zip, &e1, &e2) != CC_ITER_END) {
        if (strcmp((char *)e1, str_b) == 0)
            deque_zip_iter_remove(&zip, &r1, &r2);
    }
    ASSERT(strcmp(str_b, (char *)r1) == 0);
    ASSERT(strcmp(str_f, (char *)r2) == 0);
    ASSERT(0 == deque_contains(deque, str_b));
    ASSERT(0 == deque_contains(deque, str_f));
    ASSERT(3 == deque_size(deque));
    ASSERT(2 == deque_size(d2));
    deque_destroy(d2);

    teardown_tests();
    return 0;
}
