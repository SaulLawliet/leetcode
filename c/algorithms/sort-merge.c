/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include "c/algorithms/sort.h"

#include <stdint.h> /* INT32_MAX */
#include <stdlib.h> /* malloc(), free() */

static void merge(int *a, int p, int q, int r) {
  int i, j, k;

  /* 1. 创建临时空间 */
  int n1 = q - p + 1;
  int *L = malloc(sizeof(int) * (n1+1));
  for (i = 0; i < n1; ++i)
    L[i] = a[p+i];
  L[n1] = INT32_MAX;

  int n2 = r - q;
  int *R = malloc(sizeof(int) * (n2+1));
  for (j = 0; j < n2; ++j)
    R[j] = a[q+j+1];
  R[n2] = INT32_MAX;
  i = 0, j = 0;

  /* 2. 合并数组 */
  for (k = p; k <= r; ++k)
    a[k] = L[i] <= R[j] ? L[i++] : R[j++];

  /* 3. 释放临时空间 */
  free(L);
  free(R);
}

static void sort(int *a, int p, int r) {
  if (p >= r) return;
  int q = (p + r) / 2;
  sort(a, p, q);
  sort(a, q+1, r);
  merge(a, p, q, r);
}

void sortMerge(int *a, int len) {
  sort(a, 0, len - 1);
}
