#include "queue.h"
#include "utils.h"
#include <gillian-c/gillian-c.h>

static Queue *q;
static Queue *q2;
static int stat;

void setup_test() {
    stat = queue_new(&q);
    queue_new(&q2);
}

void teardown_test() {
    queue_destroy(q);
    queue_destroy(q2);
}

int main() {
    setup_test();

    symb_str(a);
    symb_str(b);
    symb_str(c);
    symb_str(d);
    symb_str(e);
    symb_str(f);
    symb_str(g);

    queue_enqueue(q, str_a);
    queue_enqueue(q, str_b);
    queue_enqueue(q, str_c);
    queue_enqueue(q, str_d);

    queue_enqueue(q2, str_e);
    queue_enqueue(q2, str_f);
    queue_enqueue(q2, str_g);

    QueueZipIter zip;
    queue_zip_iter_init(&zip, q, q2);

    size_t i = 0;

    void *e1, *e2;
    while (queue_zip_iter_next(&zip, &e1, &e2) != CC_ITER_END) {
        if (i == 0) {
            ASSERT(strcmp(str_d, (char *)e1) == 0);
            ASSERT(strcmp(str_g, (char *)e2) == 0);
        }
        if (i == 2) {
            ASSERT(strcmp(str_b, (char *)e1) == 0);
            ASSERT(strcmp(str_e, (char *)e2) == 0);
        }
        i++;
    }
    ASSERT(3 == i);

    teardown_test();
    return 0;
}
