#include "treetable.h"
#include "utils.h"
#include <gillian-c/gillian-c.h>

static TreeTable *table;

int main() {
    treetable_new(cmp, &table);

    int pa = __builtin_annot_intval("symb_int", pa);
    int pb = __builtin_annot_intval("symb_int", pb);
    int pc = __builtin_annot_intval("symb_int", pc);

    ASSUME(pa < pb && pb < pc);

    char a = (char)__builtin_annot_intval("symb_int", a);

    char str_a[] = {a, '\0'};

    char b = (char)__builtin_annot_intval("symb_int", b);

    char str_b[] = {b, '\0'};

    char c = (char)__builtin_annot_intval("symb_int", c);

    char str_c[] = {c, '\0'};

    treetable_add(table, &pa, str_a);
    treetable_add(table, &pb, str_b);
    treetable_add(table, &pc, str_c);

    TreeTableIter iter;
    treetable_iter_init(&iter, table);

    TreeTableEntry entry;
    while (treetable_iter_next(&iter, &entry) != CC_ITER_END) {
        int const *key = entry.key;

        if (*key == pb) {
            ASSERT(CC_OK == treetable_iter_remove(&iter, NULL));

            ASSERT(CC_ERR_KEY_NOT_FOUND == treetable_iter_remove(&iter, NULL));
        }
    }

    ASSERT(2 == treetable_size(table));
    ASSERT(0 == treetable_contains_key(table, &pb));

    treetable_destroy(table);
}
