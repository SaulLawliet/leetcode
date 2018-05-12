/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include "c/algorithms/sort.h"

void sortInsertion(int *a, int len) {
  int i, j, key;
  for (j = 1; j < len; ++j) {
    key = a[j];
    i = j - 1;
    while (i >= 0 && a[i] > key) {
      a[i+1] = a[i];
      --i;
    }
    a[i+1] = key;
  }
}
