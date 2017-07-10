/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include <stdint.h>  /* uint32_t */
#include "../test.h"

uint32_t reverseBits(uint32_t n) {
  uint32_t rt = 0;
  for (int i = 0; i < (int)sizeof(uint32_t) * 8; ++i) {
    rt = (rt << 1) + (n & 1);
    n = n >> 1;
  }
  return rt;
}

void test(uint32_t expect, uint32_t n) {
  EXPECT_EQ_INT(expect, reverseBits(n));
}

/*
  For example,
  given input 43261596 (represented in binary as 00000010100101000001111010011100),
  return 964176192 (represented in binary as 00111001011110000010100101000000).
 */
int main(void) {
  test(964176192, 43261596);

  return testOutput();
}
