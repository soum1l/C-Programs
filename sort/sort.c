#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Tuple {
    int key;
    int val;
} Tuple;

bool
less_than_tuple(const void* a, const void* b)
{
    return ((Tuple*)(a))-> key < ((Tuple*)(b))-> key;
}

void*
merge(    const void*       a
      ,   const void*       b
      ,   size_t            len_a
      ,   size_t            len_b
      ,   size_t            t_size
      ,   bool              less_than(const void*, const void*)
){
    void* c = calloc(len_a + len_b, t_size);
    void* w = c;

    size_t i=0, j=0;

    while (i < len_a && j < len_b)
    {
        if (!(*less_than)(b, a))
        {
            memcpy(w, a, t_size);
            a += t_size;
            i++;
        } else {
            memcpy(w, b, t_size);
            b += t_size;
            j++;
        }
        w += t_size;
    }

    while (i++ < len_a)
    {
        memcpy(w, a, t_size);
        a += t_size;
        w += t_size;
    }

    while (j++ < len_b)
    {
        memcpy(w, b, t_size);
        b += t_size;
        w += t_size;
    }

    return c;
}

void 
mergeSort(  void*           arr
        ,   size_t          len
        ,   size_t          t_size
        ,   bool            (*less_than)(const void*, const void*)
){
    if (len <= 1)
        return;

    /// sort segments (in place)

    void* left = arr;
    size_t len_left = len / 2;
    mergeSort(left, len_left, t_size, less_than);

    void* right= arr + (len_left * t_size);
    size_t len_right= len - len_left;
    mergeSort(right, len_right, t_size, less_than);

    ///////////// merge segments

    void* res = merge(left, right, len_left, len_right, t_size, less_than);
    memcpy(arr, res, len * t_size);
    free(res);
}

void
radixSort(  int*            arr
        ,   size_t          len
        ,   size_t          digits
        ,   void            (*stable_sort)(void*, size_t, size_t, bool (*)(const void*, const void*))
){
    Tuple* t_arr = calloc(len, sizeof(Tuple));

    //// sort using each digit

    for (size_t i=1, e=1; i <= digits; i++, e*=10)
    {
        for (size_t j=0; j < len; j++)
        {
            t_arr[j].val = arr[j];
            t_arr[j].key = (arr[j] % (e*10)) / e;
        }

        stable_sort(t_arr, len, sizeof(Tuple), &less_than_tuple);

        for (size_t j=0; j < len; j++)
            arr[j] = t_arr[j].val;
    }

    free(t_arr);
}

bool
less_than_int(const void* a, const void* b)
{
    return *(int*)(a) < *(int*)(b);
}

int
main()
{
    int a[] = { 23,21,11,45,21,86,58,44,89,5 };

    const size_t len_a = sizeof(a)/sizeof(int);

    radixSort(a, len_a, 2, &mergeSort);

    for (int i = 0; i < len_a; i++)
        printf("%d ", a[i]);

    printf("\n");

    return 0;
}
