#include <assert.h>
#include <stdio.h>
#include "compare.h"

int main(void)
{
    uint8_t diff_first[4] = {99, 20, 30, 40};
    uint8_t diff_second[4] = {10, 30, 30, 40};
    uint8_t diff_last[4] = {10, 20, 30, 90};   
    uint8_t a[4]    = {10, 20, 30, 40};
    uint8_t same[4] = {10, 20, 30, 40};

    /*fully same */
    assert(early_exit_equal(a, same, 4) == 1);
    assert(constant_time_equal(a, same, 4) == 1);

    /* only the first byte differs */
    assert(early_exit_equal(a, diff_first, 4) == 0);
    assert(constant_time_equal(a, diff_first, 4) == 0);
    /* only the last byte differs  */
    assert(early_exit_equal(a, diff_last, 4) == 0);
    assert(constant_time_equal(a, diff_last, 4) == 0);
    /* only the second byte differs  */
    assert(early_exit_equal(a, diff_second, 4) == 0);
    assert(constant_time_equal(a, diff_second, 4) == 0);
    /* nothing to compare */
    assert(early_exit_equal(a, same, 0) == 1);
    assert(constant_time_equal(a, same, 0) == 1);

    printf("all tests passed\n");
    return 0;
}