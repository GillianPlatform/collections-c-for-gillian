#include "treetable.h"
#include "utils.h"
#include <gillian-c/gillian-c.h>

static TreeTable *table;

int main() {
    treetable_new(cmp, &table);

    int pa = __builtin_annot_intval("symb_int", pa);
    int pb = __builtin_annot_intval("symb_int", pb);
    int pc = __builtin_annot_intval("symb_int", pc);

    char a = (char)__builtin_annot_intval("symb_int", a);

    char str_a[] = {a, '\0'};

    char b = (char)__builtin_annot_intval("symb_int", b);

    char str_b[] = {b, '\0'};

    ASSUME(pa != pb);

    treetable_add(table, &pa, str_a);
    treetable_add(table, &pb, str_b);

    char *ra;
    char *rb;

    treetable_get(table, &pa, (void *)&ra);
    treetable_get(table, &pb, (void *)&rb);

    ASSERT(strcmp(ra, str_a) == 0);
    ASSERT(strcmp(rb, str_b) == 0);

    treetable_destroy(table);
}
