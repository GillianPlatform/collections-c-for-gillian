#include "treetable.h"
#include "utils.h"
#include <gillian-c/gillian-c.h>

static TreeTable *table;

int main() {
    treetable_new(cmp, &table);

    int pa = __nondet_int();
    int pb = __nondet_int();
    int pc = __nondet_int();
    int pd = __nondet_int();

    char a = (char)__nondet_int();

    char str_a[] = {a, '\0'};

    char b = (char)__nondet_int();

    char str_b[] = {b, '\0'};

    char c = (char)__nondet_int();

    char str_c[] = {c, '\0'};

    char d = (char)__nondet_int();

    char str_d[] = {d, '\0'};

    __CPROVER_assume(pa < pb && pb < pc && pc < pd);

    treetable_add(table, &pc, str_a);
    treetable_add(table, &pd, str_b);
    treetable_add(table, &pb, str_c);
    treetable_add(table, &pa, str_d);

    int *last;
    treetable_get_last_key(table, (void *)&last);

    __CPROVER_assert(pd == *last, "")

    treetable_destroy(table);
}
