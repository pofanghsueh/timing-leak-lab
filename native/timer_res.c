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
    uint64_t delta = 0;

    do {
        uint64_t t0 = now_ns();
        uint64_t t1 = now_ns();
        delta = t1 - t0; 
    } while (delta == 0);

    printf("Minimum observed delta: %" PRIu64 " ns\n", delta);

    return 0;
}