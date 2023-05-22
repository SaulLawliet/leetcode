/*
 * Copyright (C) 2022, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 两个指针, 模拟实际操作过程即可
 * 第一次提交的时候, 没有考虑到这个情况: ".L.R."
 */

#include <stdbool.h>
#include "c/test.h"

char *pushDominoes(char *dominoes) {
  int slow = 0, fast = 0;

  for (; dominoes[fast] != '\0'; fast++) {
    if (dominoes[fast] == 'L') {
      if (dominoes[slow] == 'L' || dominoes[slow] == '.') {
        // all set 'L'
        while (slow < fast) dominoes[slow++] = 'L';
      } else {
        // 此时是R, 向中间靠拢
        int mid = (fast + slow) / 2;
        bool even = (fast + slow) % 2 == 0;
        while (slow < mid) dominoes[slow++] = 'R';

        if (even)
          slow++;
        else
          dominoes[slow++] = 'R';

        while (slow < fast) dominoes[slow++] = 'L';
      }
    } else if (dominoes[fast] == 'R') {
      if (dominoes[slow] == 'L' || dominoes[slow] == '.') {
        // 忽略
        slow = fast;
      } else {
        // all set 'R'
        while (slow < fast) dominoes[slow++] = 'R';
      }
    }
  }

  // 注意, 如何最后一次操作是‘R’, 要把后面都推倒
  if (dominoes[slow] == 'R') {
    while (slow < fast) dominoes[slow++] = 'R';
  }

  return dominoes;
}

void test(const char *expect, const char *dominoes) {
  int len = strlen(dominoes) + 1;
  char *str = malloc(sizeof(char) * len);
  memcpy(str, dominoes, len);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, pushDominoes(str));
}

int main(void) {
  test("RR.L", "RR.L");
  test("LL.RR.LLRRLL..", ".L.R...LR..L..");

  test("LL.RR", ".L.R.");

  return testOutput();
}
