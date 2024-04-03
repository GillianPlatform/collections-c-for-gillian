#include "treeset.h"
#include "utils.h"

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

    treeset_remove_all(set);

    __CPROVER_assert(0 == treeset_size(set), "");
    __CPROVER_assert(0 == treeset_contains(set, &a), "");
    __CPROVER_assert(0 == treeset_contains(set, &b), "");
    __CPROVER_assert(0 == treeset_contains(set, &c), "");
}
