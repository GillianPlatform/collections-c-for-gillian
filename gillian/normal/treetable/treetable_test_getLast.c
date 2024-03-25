#include "treetable.h"
#include "utils.h"
#include <gillian-c/gillian-c.h>

static TreeTable *table;

int main() {
    treetable_new(cmp, &table);

    int pa = __builtin_annot_intval("symb_int", pa);
    int pb = __builtin_annot_intval("symb_int", pb);
    int pc = __builtin_annot_intval("symb_int", pc);
    int pd = __builtin_annot_intval("symb_int", pd);

    char a = (char)__builtin_annot_intval("symb_int", a);

    char str_a[] = {a, '\0'};

    char b = (char)__builtin_annot_intval("symb_int", b);

    char str_b[] = {b, '\0'};

    char c = (char)__builtin_annot_intval("symb_int", c);

    char str_c[] = {c, '\0'};

    char d = (char)__builtin_annot_intval("symb_int", d);

    char str_d[] = {d, '\0'};

    ASSUME(pa < pb && pb < pc && pc < pd);

    treetable_add(table, &pc, str_a);
    treetable_add(table, &pd, str_b);
    treetable_add(table, &pb, str_c);
    treetable_add(table, &pa, str_d);

    int *last;
    treetable_get_last_key(table, (void *)&last);

    ASSERT(pd == *last);

    treetable_destroy(table);
}
