/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.

 * 需要考虑几个问题:
 *   1. 字符串最前面的空格
 *   2. 正, 负号
 *   3. 遇到非数字的时候终止
 *   4. 整型溢出时, 取 MAX/MIN
 */

#include <ctype.h>   /* isdigit() */
#include <limits.h>  /* INT_MAX, INT_MIN */
#include "../test.h"

int myAtoi(char *str) {
  char *p = str;
  while (*p == ' ') p++;  /* 处理之前的空格 */

  int sign = 1;
  if (*p == '+' || *p == '-') {
    sign = 1 - (*p++ - '+');
  }

  int rt = 0;
  while (isdigit(*p)) {
    if (rt > INT_MAX / 10 ||
        (rt == INT_MAX / 10 && *p > '7')) {
      return sign == 1 ? INT_MAX : INT_MIN;
    }
    rt = rt * 10 + *p++ - '0';
  }
  return rt * sign;
}

void test(int expect, char *str) {
  EXPECT_EQ_INT(expect, myAtoi(str));
}

int main(void) {
  test(123, "  +123");
  test(-123, "  -123");
  test(1, "  1a123");
  test(INT_MAX, "9999999999999999999999999");
  test(INT_MIN, "-9999999999999999999999999");

  return testOutput();
}
