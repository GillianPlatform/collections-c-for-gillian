#include "array.h"
#include <gillian-c/gillian-c.h>

static Array *v1;
static Array *v2;
static ArrayConf vc;
static int stat;

int main(int a, int b, int c) {
    stat = array_new(&v1);
    ASSERT(stat == CC_OK);

    array_add(v1, &a);
    array_add(v1, &b);
    array_add(v1, &c);

    int *ar;
    int *br;
    int *cr;

    array_get_at(v1, 0, (void *)&ar);
    array_get_at(v1, 1, (void *)&br);
    array_get_at(v1, 2, (void *)&cr);

    ASSERT(a == *ar);
    ASSERT(b == *br);
    ASSERT(c == *cr);

    array_destroy(v1);

    return 0;
}
