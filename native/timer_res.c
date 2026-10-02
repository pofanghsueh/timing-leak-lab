#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <inttypes.h>

static uint64_t now_ns(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
}

int main(void)
{
    uint64_t delta[20];

    for (int i=0; i<20; i++)
    {
        uint64_t t0 = now_ns();
        uint64_t t1 = now_ns();
        delta[i] = t1 - t0; 
    } 
    for (int i=0; i<20; i++)
    {
        printf("%"PRIu64"\n", delta[i]);
    } 
    return 0;
}