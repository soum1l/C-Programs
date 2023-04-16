#include <stdlib.h>
#include <string.h>

void*
foldr(  const void*     arr
    ,   size_t          len
    ,   size_t          arr_t_size
    ,   void*           (*combine_r)(const void*, void*)
    ,   void* const     initial
){
    if (0 < len--) {
        return combine_r(
                arr
            ,   foldr(  (void*)(arr + arr_t_size)
                    ,   len
                    ,   arr_t_size
                    ,   combine_r
                    ,   initial
                )
        );
    } else { return initial; }
}

void*
foldr1( const void*     arr
    ,   size_t          len
    ,   size_t          arr_t_size
    ,   void*           (*combine_r)(const void*, void*)
    ,   void* const     result
){
    return foldr(   arr
                ,   --len
                ,   arr_t_size
                ,   combine_r
                ,   memcpy(result, arr + (len * arr_t_size), arr_t_size)
    );
}

void*
foldl(  const void*     arr
    ,   size_t          len
    ,   size_t          arr_t_size
    ,   void*           (*combine_l)(void*, const void*)
    ,   void* const     initial
){
    if (0 < len--) {
        return combine_l(
                foldl(  arr
                    ,   len
                    ,   arr_t_size
                    ,   combine_l
                    ,   initial
                )
            ,   (void*)(arr + (arr_t_size * len))
        );
    } else { return initial; }
}

void*
foldl1( const void*     arr
    ,   size_t          len
    ,   size_t          arr_t_size
    ,   void*           (*combine_l)(void*, const void*)
    ,   void* const     result
){
    return foldl(   arr
                ,   --len
                ,   arr_t_size
                ,   combine_l
                ,   memcpy(result, arr + (len * arr_t_size), arr_t_size)
    );
}
