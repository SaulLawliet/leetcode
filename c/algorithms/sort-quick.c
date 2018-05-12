/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include "c/algorithms/sort.h"

static void exchange(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

static int partition(int *a, int p, int r) {
  int i, j, x = a[r];
  for (i = p - 1, j = p; j < r; ++j) {
    if (a[j] <= x) {
      i++;
      exchange(&a[i], &a[j]);
    }
  }
  exchange(&a[i+1], &a[r]);
  return i+1;
}

static void sort(int *a, int p, int r) {
  if (p >= r) return;
  int q = partition(a, p, r);
  sort(a, p, q-1);
  sort(a, q+1, r);
}

void sortQuick(int *a, int len) {
  sort(a, 0, len - 1);
}
