#include "folds.c"

#include <stdlib.h>
#include <stdio.h>

#define TYPE int

void*
prepend(const void* obj, void* arr)
{
    *(TYPE*)(arr) = *(TYPE*)(obj);
    return arr + sizeof(TYPE);
}

int
main()
{
    TYPE arr[] = { 1,2,3,4,5,6,7,8 };

    TYPE* rev_arr = malloc(sizeof(arr));

    const size_t len = sizeof(arr)/sizeof(*arr);

    foldr(&arr, len, sizeof(TYPE), &prepend, rev_arr);

    for (int i = 0; i < len; i++)
        printf("%d ", rev_arr[i]);

    printf("\n");

    free(rev_arr);

    return 0;
}