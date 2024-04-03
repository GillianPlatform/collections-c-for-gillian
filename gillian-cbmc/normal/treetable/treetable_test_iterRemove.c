#include "treetable.h"
#include "utils.h"

static TreeTable *table;

int main() {
    treetable_new(cmp, &table);

    int pa = __nondet_int();
    int pb = __nondet_int();
    int pc = __nondet_int();

    __CPROVER_assume(pa < pb && pb < pc);

    char a = (char)__nondet_int();

    char str_a[] = {a, '\0'};

    char b = (char)__nondet_int();

    char str_b[] = {b, '\0'};

    char c = (char)__nondet_int();

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
            __CPROVER_assert(CC_OK == treetable_iter_remove(&iter, NULL), "");

            __CPROVER_assert(CC_ERR_KEY_NOT_FOUND == treetable_iter_remove(&iter, NULL), "");
        }
    }

    __CPROVER_assert(2 == treetable_size(table), "");
    __CPROVER_assert(0 == treetable_contains_key(table, &pb), "");

    treetable_destroy(table);
}
