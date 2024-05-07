#include <assert.h>

#include "pqueue.h"

static int comp(const void *pa, const void *pb) {
    int a = *((int *)pa), b = *((int *)pb);
    if (a > b) {
        return 1;
    } else {
        return -1;
    }
}

int main() {
    PQueue *p1;
    pqueue_new(&p1, comp);
    int a = 1;
    int b = 0;

    pqueue_push(p1, (void *)&b);
    pqueue_push(p1, (void *)&a);
    return 0;
}
