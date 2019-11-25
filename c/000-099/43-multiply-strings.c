/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 两个大于0的数相乘, 结果的长度一定是两个数的长度和 或 两个数的长度和减1
 * 假设, a * b = c, 则
 *   len(c) == len(a) + len(b)
 * OR
 *   len(c) == len(a) + len(b) - 1
 * 然后从低位往高位计算, 最后如果首位为0时, 则字符前移
 */

#include <stdlib.h> /* malloc(), memset() */
#include <string.h> /* strncpy(), strlen() */
#include "c/test.h"

char *multiply(char *num1, char *num2) {
  char *rtn;

  if (*num1 == '0' || *num2 == '0')
    return strncpy((rtn = malloc(sizeof(char) * 2)), "0", 2);

  int len1 = strlen(num1), len2 = strlen(num2);
  memset((rtn = malloc(sizeof(char) * (len1 + len2 + 1))), 0, len1 + len2 + 1);

  for (int i = len1 - 1; i >= 0; --i) {
    for (int j = len2 - 1; j >= 0; --j) {
      int v = (num1[i] - '0') * (num2[j] - '0') + rtn[i + j + 1];
      rtn[i + j + 1] = v % 10;
      rtn[i + j] += v / 10;
    }
  }

  int i = 0, flag = rtn[0] == 0 ? 1 : 0;
  while (flag < len1 + len2)
    rtn[i++] = rtn[flag++] + '0';
  rtn[i] = '\0';
  return rtn;
}

void test(const char *expect, char *num1, char *num2) {
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, multiply(num1, num2));
}

int main(void) {
  test("0", "0", "0");
  test("1", "1", "1");
  test("98901", "99", "999");
  test("1000", "10", "100");

  return testOutput();
}
