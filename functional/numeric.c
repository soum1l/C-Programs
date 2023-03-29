#include "folds.c"

#include <stdio.h>

#define NUMTYPE int

/* COMBINATORS */

void*
add_r(const void* lhs, void* rhs)
{
    *(NUMTYPE*)rhs += *(NUMTYPE*)lhs;
    return rhs;
}

void*
add_l(void* lhs, const void* rhs)
{
    return add_r(rhs, lhs);
}

void*
sub_r(const void* lhs, void* rhs)
{
    *(NUMTYPE*)rhs -= *(NUMTYPE*)lhs;
    return rhs;
}

void*
sub_l(void* lhs, const void* rhs)
{
    *(NUMTYPE*)lhs -= *(NUMTYPE*)rhs;
    return lhs;
}

void*
mul_r(const void* lhs, void* rhs)
{
    *(NUMTYPE*)rhs *= *(NUMTYPE*)lhs;
    return rhs;
}

void*
mul_l(void* lhs, const void* rhs)
{
    return mul_r(rhs, lhs);
}

int
main()
{
    NUMTYPE arr[] = {1,2,3,4,5,6};

    NUMTYPE* res = malloc(sizeof(NUMTYPE));
    *res = 1;

    const size_t len = sizeof(arr)/sizeof(*arr);

    foldr(arr, len, sizeof(NUMTYPE), &mul_r, res);

    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);

    printf("\n%d\n", *res);

    free(res);

    return 0;
}