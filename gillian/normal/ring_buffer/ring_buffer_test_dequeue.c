#include "ring_buffer.h"
#include "utils.h"
#include <gillian-c/gillian-c.h>

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
    uint64_t out;
    for (int i = 0; i < 10; i++) {
        rbuf_dequeue(rbuf, &out);
        ASSERT(items[i] == out);
        memset(&out, 0, sizeof(uint64_t));
    }

    teardown_test();
    return 0;
}
