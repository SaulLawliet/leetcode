/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 朴素方法, 模拟自然书写(速度比较慢)
 *
 * ps. 更简单的方法是定义几个常量 -> 个位0-9, 十位0-9, 百位0-9, 千位0-3
 * 然后根据给定的数字从高位到低位依次转换并拼接起来
 */

#include <stdlib.h>  /* malloc() */
#include <math.h>    /* pow() */
#include "../test.h"

const char T[4][3] = {
  /*1    5    10 */
  {'M', ' ', ' '},  /* thousand */
  {'C', 'D', 'M'},  /* hundred */
  {'X', 'L', 'C'},  /* ten */
  {'I', 'V', 'X'}   /* one */
};

char* intToRoman(int num) {
  /* 在3999内, 最长的结果是 3888(MMMDCCCLXXXVIII) */
  char *rt = malloc(sizeof(char) * 16);  /* 15 + 1 */
  char *p = rt;

  int i, v, bit;
  for (i = 0; i < 4; i++) {
    bit = pow(10, 3 - i);  /* 0 -> 1000, 1 -> 100, 2 -> 10, 3 -> 1 */
    v = num / bit;
    if (v != 0) {
      if (bit != 1) num %= bit;
      if (v == 9) {
        *p++ = T[i][0];
        *p++ = T[i][2];
      } else if (v == 4) {
        *p++ = T[i][0];
        *p++ = T[i][1];
      } else {
        if (v >= 5) {
          v -= 5;
          *p++ = T[i][1];
        }
        while (v--) *p++ = T[i][0];
      }
    }
  }
  *p = '\0';
  return rt;
}

void test(const char* expect, int num) {
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, intToRoman(num));
}

int main(void) {
  test("I", 1);
  test("IV", 4);
  test("MMMDCCCLXXXVIII", 3888);

  return testOutput();
}
