/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#ifndef C_TOOLS_SWAP_H_
#define C_TOOLS_COMPARE_H_

void swap_ints(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

#endif /* C_TOOLS_SWAP_H_ */
