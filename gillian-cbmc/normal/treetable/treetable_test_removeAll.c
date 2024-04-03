#include "treetable.h"
#include "utils.h"

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

    treetable_add(table, &pa, str_a);
    treetable_add(table, &pb, str_b);
    treetable_add(table, &pc, str_c);

    treetable_remove_all(table);

    __CPROVER_assert(0 == treetable_contains_key(table, &pa), "");
    __CPROVER_assert(0 == treetable_contains_key(table, &pb), "");
    __CPROVER_assert(0 == treetable_contains_key(table, &pc), "");

    treetable_destroy(table);
}
