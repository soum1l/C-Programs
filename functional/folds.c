#include <stdlib.h>

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