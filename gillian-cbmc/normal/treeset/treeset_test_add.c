#include "treeset.h"
#include "utils.h"
#include <gillian-c/gillian-c.h>

static TreeSet *set;

int main() {
    treeset_new(cmp, &set);

    int a = __nondet_int();
    int b = __nondet_int();
    int c = __nondet_int();
    __CPROVER_assume(a != b && a != c && b != c);

    treeset_add(set, &a);
    treeset_add(set, &b);
    treeset_add(set, &c);
    treeset_add(set, &c);

    __CPROVER_assert(3 == treeset_size(set), "")
    __CPROVER_assert(1 == treeset_contains(set, &a), "")
    __CPROVER_assert(1 == treeset_contains(set, &b), "")
}
