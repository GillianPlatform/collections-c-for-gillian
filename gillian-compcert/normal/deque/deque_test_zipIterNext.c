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

    size_t i = 0;

    void *e1, *e2;
    while (deque_zip_iter_next(&zip, &e1, &e2) != CC_ITER_END) {
        if (i == 0) {
            ASSERT(strcmp(str_a, (char *)e1) == 0);
            ASSERT(strcmp(str_e, (char *)e2) == 0);
        }
        if (i == 2) {
            ASSERT(strcmp(str_c, (char *)e1) == 0);
            ASSERT(strcmp(str_g, (char *)e2) == 0);
        }
        i++;
    }
    ASSERT(3 == i);
    deque_destroy(d2);

    teardown_tests();
    return 0;
}
