#include "treetable.h"
#include "utils.h"

static TreeTable *table;

int main() {
    treetable_new(cmp, &table);

    int pa = __nondet_int();
    int pb = __nondet_int();
    int pc = __nondet_int();
    int pd = __nondet_int();

    __CPROVER_assume(pa < pb && pb < pd && pd < pc);

    char a = (char)__nondet_int();

    char str_a[] = {a, '\0'};

    char b = (char)__nondet_int();

    char str_b[] = {b, '\0'};

    char c = (char)__nondet_int();

    char str_c[] = {c, '\0'};

    char d = (char)__nondet_int();

    char str_d[] = {d, '\0'};

    treetable_add(table, &pc, str_a);
    treetable_add(table, &pd, str_b);
    treetable_add(table, &pb, str_c);
    treetable_add(table, &pa, str_d);

    int one = 0;
    int two = 0;
    int three = 0;
    int four = 0;

    TreeTableIter iter;
    treetable_iter_init(&iter, table);

    TreeTableEntry entry;
    while (treetable_iter_next(&iter, &entry) != CC_ITER_END) {
        int const *key = entry.key;

        if (*key == pa)
            one++;

        if (*key == pb)
            two++;

        if (*key == pc)
            three++;

        if (*key == pd)
            four++;
    }

    __CPROVER_assert(1 == one, "");
    __CPROVER_assert(1 == two, "");
    __CPROVER_assert(1 == three, "");
    __CPROVER_assert(1 == four, "");

    treetable_destroy(table);
}
