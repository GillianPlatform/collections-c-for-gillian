#include "treetable.h"
#include "utils.h"
#include <gillian-c/gillian-c.h>

static TreeTable *table;

int main() {
    treetable_new(cmp, &table);

    int pa = __nondet_int();
    int pb = __nondet_int();
    int pc = __nondet_int();

    char a = (char)__nondet_int();

    char str_a[] = {a, '\0'};

    char b = (char)__nondet_int();

    char str_b[] = {b, '\0'};

    __CPROVER_assume(pa != pb);

    treetable_add(table, &pa, str_a);
    treetable_add(table, &pb, str_b);

    char *ra;
    char *rb;

    treetable_get(table, &pa, (void *)&ra);
    treetable_get(table, &pb, (void *)&rb);

    __CPROVER_assert(strcmp(ra, str_a) == 0, "")
    __CPROVER_assert(strcmp(rb, str_b) == 0, "")

    treetable_destroy(table);
}
