/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#ifndef C_TOOLS_COMPARE_H_
#define C_TOOLS_COMPARE_H_

int compare_ints(const void *a, const void *b) {
  int arg1 = *(const int *)a;
  int arg2 = *(const int *)b;
  if (arg1 < arg2) return -1;
  if (arg1 > arg2) return 1;
  return 0;
}

#endif /* C_TOOLS_COMPARE_H_ */
