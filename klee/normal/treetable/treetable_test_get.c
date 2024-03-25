#include "treetable.h"
#include "utils.h"
#include <klee/klee.h> 

static TreeTable *table;

int main() {
    treetable_new(cmp, &table);

    int pa; klee_make_symbolic(&pa, sizeof(int), "pa");
    int pb; klee_make_symbolic(&pb, sizeof(int), "pb");
    int pc; klee_make_symbolic(&pc, sizeof(int), "pc");

    char a; klee_make_symbolic(&a, sizeof(char), "a");

    char str_a[] = {a, '\0'};

    char b; klee_make_symbolic(&b, sizeof(char), "b");

    char str_b[] = {b, '\0'};

    klee_assume(pa != pb);

    treetable_add(table, &pa, str_a);
    treetable_add(table, &pb, str_b);

    char *ra;
    char *rb;

    treetable_get(table, &pa, (void *)&ra);
    treetable_get(table, &pb, (void *)&rb);

    klee_assert(strcmp(ra, str_a) == 0);
    klee_assert(strcmp(rb, str_b) == 0);

    treetable_destroy(table);
}
