/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 罗马数字含义:
 * I, V,  X,  L,   C,   D,    M
 * 1, 5, 10, 50, 100, 500, 1000
 *
 * 正常情况都是累加, 以下情况除外:
 * IV, IX -- 4, 9
 * XL, XC -- 40, 90
 * CD, CM -- 400, 900
 */

#include "../test.h"

int romanToInt(char *s) {
  int rt = 0;
  char *p = s;
  while (*p) {
    switch (*p++) {
      /* 此时 *p 已经后移了 */
      case 'I':
        if (*p != '\0' && (*p == 'V' || *p == 'X'))
          rt -= 1;
        else
          rt += 1;
        break;
      case 'X':
        if (*p != '\0' && (*p == 'L' || *p == 'C'))
          rt -= 10;
        else
          rt += 10;
        break;
      case 'C':
        if (*p != '\0' && (*p == 'D' || *p == 'M'))
          rt -= 100;
        else
          rt += 100;
        break;
      case 'V': rt += 5; break;
      case 'L': rt += 50; break;
      case 'D': rt += 500; break;
      case 'M': rt += 1000; break;
    }
  }
  return rt;
}

void test(int expect, char *s) {
  EXPECT_EQ_INT(expect, romanToInt(s));
}

int main(void) {
  test(1, "I");
  test(4, "IV");
  test(40, "XL");

  return testOutput();
}
