#include "deque.h"
#include "utils.h"

static Deque *deque;
static DequeConf conf;
int stat;

void setup_tests() { stat = deque_new(&deque); }

void teardown_tests() { deque_destroy(deque); }

int main() {
    setup_tests();

    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    int *c = malloc(sizeof(int));

    int va = __nondet_int();
    int vb = __nondet_int();
    int vc = __nondet_int();

    *a = va;
    *b = vb;
    *c = vc;

    deque_add_last(deque, a);
    deque_add_last(deque, b);
    deque_add_last(deque, c);

    Deque *cpy;
    deque_copy_deep(deque, copy, &cpy);

    int size = deque_size(cpy);
    __CPROVER_assert(3 == size, "");

    int *ca;
    deque_get_at(cpy, 0, (void *)&ca);
    int *cb;
    deque_get_at(cpy, 1, (void *)&cb);
    int *cc;
    deque_get_at(cpy, 2, (void *)&cc);

    __CPROVER_assert(va == *ca, "");
    __CPROVER_assert(vb == *cb, "");
    __CPROVER_assert(vc == *cc, "");
    deque_destroy_cb(cpy, free);
    free(a);
    free(b);
    free(c);

    teardown_tests();
    return 0;
}
