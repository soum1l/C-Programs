#include <stdio.h>
#include <stdlib.h>

#define NUMTYPE int

/* FOLDS */

void*
foldr(  const void*     arr
    ,   size_t          len
    ,   size_t          arr_t_size
    ,   void*           (*combine_r)(const void*, void*)
    ,   void* const     initial
){
    if (len-- > 0)
        return combine_r(
                arr
            ,   foldr(  (void*)(arr + arr_t_size)
                    ,   len
                    ,   arr_t_size
                    ,   combine_r
                    ,   initial
                )
        );
    else
        return initial;
}

void*
foldl(  const void*     arr
    ,   size_t          len
    ,   size_t          arr_t_size
    ,   void*           (*combine_l)(void*, const void*)
    ,   void* const     initial
){
    if (len-- > 0)
        return combine_l(
                foldl(  arr
                    ,   len
                    ,   arr_t_size
                    ,   combine_l
                    ,   initial
                )
            ,   (void*)(arr + (arr_t_size * len))
        );
    else
        return initial;
}

/* COMBINATORS */

void*
add_r_NUMTYPE(const void* lhs, void* rhs)
{
    *(NUMTYPE*)rhs += *(NUMTYPE*)lhs;
    return rhs;
}

void*
add_l_NUMTYPE(void* lhs, const void* rhs)
{
    return add_r_NUMTYPE(rhs, lhs);
}

void*
sub_r_NUMTYPE(const void* lhs, void* rhs)
{
    *(NUMTYPE*)rhs -= *(NUMTYPE*)lhs;
    return rhs;
}

void*
sub_l_NUMTYPE(void* lhs, const void* rhs)
{
    *(NUMTYPE*)lhs -= *(NUMTYPE*)rhs;
    return lhs;
}

void*
mul_r_NUMTYPE(const void* lhs, void* rhs)
{
    *(NUMTYPE*)rhs *= *(NUMTYPE*)lhs;
    return rhs;
}

void*
mul_l_NUMTYPE(void* lhs, const void* rhs)
{
    return mul_r_NUMTYPE(rhs, lhs);
}

int
main()
{
    NUMTYPE arr[] = {1,2,3,4,5,6};

    NUMTYPE* res = (NUMTYPE*)malloc(sizeof(NUMTYPE));
    *res = 1;

    const size_t len = sizeof(arr)/sizeof(*arr);

    foldr(arr, len, sizeof(NUMTYPE), &mul_r_NUMTYPE, res);

    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);

    printf("\n%d\n", *res);

    free(res);

    return 0;
}
