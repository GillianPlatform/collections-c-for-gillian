#include "treeset.h"
#include "utils.h"
#include <klee/klee.h> 

static TreeSet *set;

int main() {
    treeset_new(cmp, &set);

    int a; klee_make_symbolic(&a, sizeof(int), "a");
    int b; klee_make_symbolic(&b, sizeof(int), "b");
    int c; klee_make_symbolic(&c, sizeof(int), "c");
    klee_assume(a != b && a != c && b != c);

    treeset_add(set, &a);
    treeset_add(set, &b);
    treeset_add(set, &c);
    treeset_add(set, &c);

    klee_assert(3 == treeset_size(set));
    klee_assert(1 == treeset_contains(set, &a));
    klee_assert(1 == treeset_contains(set, &b));
}
