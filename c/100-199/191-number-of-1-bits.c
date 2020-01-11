/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 第一次想到的当然是蛮力, 完成后, 在讨论帖子发现了巧妙的解法
 * 即: 每次做 x & x-1 运算时, 最后一位的'1'将被移除, 当 x == 0 时, 运算了几次就有多少个'1' 
 */

#include <stdint.h>
#include "c/test.h"

int hammingWeight(uint32_t n) {
  int weight = 0;
  while (n) {
    weight += (n & 1);
    n >>= 1;
  }
  return weight;
}

int hammingWeight_v2(uint32_t n) {
  int weight = 0;
  while (n) {
    n &= n - 1;
    weight++;
  }
  return weight;
}

void test(int expect, uint32_t n) {
  EXPECT_EQ_INT(expect, hammingWeight(n));
  EXPECT_EQ_INT(expect, hammingWeight_v2(n));
}

int main(void) {
  // 0000 0000 0000 0000 0000 0000 0000 1011
  test(3, 0xB);
  // 0000 0000 0000 0000 0000 0000 1000 0000
  test(1, 0x80);
  // 1111 1111 1111 1111 1111 1111 1111 1101
  test(31, 0xFFFFFFFD);

  return testOutput();
}
