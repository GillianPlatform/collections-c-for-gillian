#include "treetable.h"
#include "utils.h"
#include <klee/klee.h> 

static TreeTable *table;

int main() {
    treetable_new(cmp, &table);

    int pa; klee_make_symbolic(&pa, sizeof(int), "pa");
    int pb; klee_make_symbolic(&pb, sizeof(int), "pb");
    int pc; klee_make_symbolic(&pc, sizeof(int), "pc");
    int pd; klee_make_symbolic(&pd, sizeof(int), "pd");

    char a; klee_make_symbolic(&a, sizeof(char), "a");

    char str_a[] = {a, '\0'};

    char b; klee_make_symbolic(&b, sizeof(char), "b");

    char str_b[] = {b, '\0'};

    char c; klee_make_symbolic(&c, sizeof(char), "c");

    char str_c[] = {c, '\0'};

    char d; klee_make_symbolic(&d, sizeof(char), "d");

    char str_d[] = {d, '\0'};

    klee_assume(pa < pb && pb < pc && pc < pd);

    treetable_add(table, &pc, str_a);
    treetable_add(table, &pd, str_b);
    treetable_add(table, &pb, str_c);
    treetable_add(table, &pa, str_d);

    int *last;
    treetable_get_last_key(table, (void *)&last);

    klee_assert(pd == *last);

    treetable_destroy(table);
}
