#include "compare.h"

int early_exit_equal(const uint8_t *a, const uint8_t *b, size_t n)
{
    for (size_t i = 0; i < n; i++) 
    {
        /* Stop at the first mismatch. */
        if (a[i]!=b[i])
        {
            return 0;
        }
    }
    return 1;
}

int constant_time_equal(const uint8_t *a, const uint8_t *b, size_t n)
{
    uint8_t diff = 0;
    for (size_t i = 0; i < n; i++) 
    {
        /* Accumulate every byte difference; never exit early. */
        diff|=a[i]^b[i];
    }
    /* diff is zero only if all bytes matched. */
    if (diff==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}