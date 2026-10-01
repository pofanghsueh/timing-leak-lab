#ifndef COMPARE_H
#define COMPARE_H

#include <stddef.h>
#include <stdint.h>

/* Return 1 if a and b are equal over n bytes, 0 otherwise. */
int early_exit_equal(const uint8_t *a, const uint8_t *b, size_t n);
int constant_time_equal(const uint8_t *a, const uint8_t *b, size_t n);

#endif