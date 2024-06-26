#include "ring_buffer.h"
#include "utils.h"

static int stat;
static Rbuf *rbuf;

void setup_test() { stat = rbuf_new(&rbuf); }

void teardown_test() { rbuf_destroy(rbuf); }

int main() {
    setup_test();

    uint64_t items[10];
    symb_uint(a);
    symb_uint(b);
    symb_uint(c);
    symb_uint(d);
    symb_uint(e);
    symb_uint(f);
    symb_uint(g);
    symb_uint(h);
    symb_uint(i);
    symb_uint(j);
    rbuf_enqueue(rbuf, a);
    rbuf_enqueue(rbuf, b);
    rbuf_enqueue(rbuf, c);
    rbuf_enqueue(rbuf, d);
    rbuf_enqueue(rbuf, e);
    rbuf_enqueue(rbuf, f);
    rbuf_enqueue(rbuf, g);
    rbuf_enqueue(rbuf, h);
    rbuf_enqueue(rbuf, i);
    rbuf_enqueue(rbuf, j);
    memset(items, 0, sizeof(uint64_t) * 10);
    items[0] = a;
    items[1] = b;
    items[2] = c;
    items[3] = d;
    items[4] = e;
    items[5] = f;
    items[6] = g;
    items[7] = h;
    items[8] = i;
    items[9] = j;

    __CPROVER_assert(items[0] == rbuf_peek(rbuf, 0), "");
    __CPROVER_assert(items[1] == rbuf_peek(rbuf, 1), "");

    symb_uint(a_test);
    symb_uint(b_test);
    rbuf_enqueue(rbuf, a_test);
    rbuf_enqueue(rbuf, b_test);

    __CPROVER_assert(rbuf_peek(rbuf, 0) == a_test, "");
    __CPROVER_assert(rbuf_peek(rbuf, 1) == b_test, "");
    uint64_t out;
    rbuf_dequeue(rbuf, &out);
    __CPROVER_assert(items[2] == out, "");

    teardown_test();
    return 0;
}
