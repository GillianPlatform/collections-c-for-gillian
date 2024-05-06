#ifndef TEST_UTILS_H
#define TEST_UTILS_H

// #include <gillian-c/gillian-c.h>
#include <stdlib.h>
#include <string.h>

#define symb_str(X)                                                            \
    char X = (char)__nondet_int();                                             \
    __CPROVER_assume(X > 0);                                                   \
    char str_##X[] = {X, '\0'}

#define symb_uint(X) uint64_t X = (uint64_t)__nondet_int()

void CHECK_EQUAL_C_STRING(char *s1, char *s2);

void *copy(void *e1);

int cmp(void const *e1, void const *e2);

int zero_if_ptr_eq(void const *e1, void const *e2);

#endif /* TEST_UTILS_H */
