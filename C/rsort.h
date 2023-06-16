#ifndef SIMPLICITY_RSORT_H
#define SIMPLICITY_RSORT_H

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "limitations.h"
#include "sha256.h"
#include "simplicity_assert.h"

_Static_assert(UCHAR_MAX < SIZE_MAX, "UCHAR_MAX >= SIZE_MAX");
#define CHAR_COUNT ((size_t)1 << CHAR_BIT)

int rsort(const sha256_midstate** a, size_t len);

/* Searches for duplicates in an array of 'sha256_midstate's.
 * If malloc fails, returns -1.
 * If no duplicates are found, returns 0.
 * If duplicates are found, returns a positive value.
 *
 * Precondition: const sha256_midstate a[len];
 *               len <= DAG_LEN_MAX;
 */
static inline int hasDuplicates(const sha256_midstate* a, size_t len) {
  if (0 == len) return 0;
  static_assert(DAG_LEN_MAX <= SIZE_MAX / sizeof(const sha256_midstate*), "perm array too large.");
  static_assert(1 <= DAG_LEN_MAX, "DAG_LEN_MAX is zero.");
  static_assert(DAG_LEN_MAX - 1 <= UINT32_MAX, "perm array index does not fit in uint32_t.");
  simplicity_assert(len <= SIZE_MAX / sizeof(const sha256_midstate*));
  simplicity_assert(len - 1 <= UINT32_MAX);
  const sha256_midstate **perm = malloc(len * sizeof(const sha256_midstate*));
  int result = perm ? 0 : -1;

  if (0 <= result) {
    for (size_t i = 0; i < len; ++i) {
      perm[i] = a + i;
    }

    result = rsort(perm, len);
  }

  free(perm);
  return result;
}

#endif
