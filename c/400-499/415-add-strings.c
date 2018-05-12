/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 思路同 No.43
 */

#include <stdlib.h> /* malloc() */
#include <string.h> /* strncpy(), strlen(), memset() */
#include "c/test.h"

char *addStrings(char *num1, char *num2) {
  char *rtn;
  int len1 = strlen(num1), len2 = strlen(num2);
  if (*num1 == '0') {
    return strncpy((rtn = malloc(len2 + 1)), num2, len2 + 1);
  }
  if (*num2 == '0') {
    return strncpy((rtn = malloc(len1 + 1)), num1, len1 + 1);
  }
  int maxLen = (len1 >= len2 ? len1 : len2) + 1; /* 进位 */
  memset((rtn = malloc(maxLen + 1)), 0, maxLen + 1);

  int v, index1, index2;
  for (int i = maxLen - 1; i > 0; --i) {
    int v = rtn[i];
    if ((index1 = len1 + i - maxLen) >= 0)
      v += num1[index1] - '0';
    if ((index2 = len2 + i - maxLen) >= 0)
      v += num2[index2] - '0';
    rtn[i] = v % 10;
    rtn[i - 1] += v / 10;
  }

  int i = 0, flag = rtn[0] == 0 ? 1 : 0;
  while (flag < maxLen)
    rtn[i++] = rtn[flag++] + '0';
  rtn[i] = '\0';
  return rtn;
}

void test(const char *expect, char *num1, char *num2) {
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, addStrings(num1, num2));
}

int main(void) {
  test("1", "0", "1");
  test("2", "2", "0");
  test("1008", "999", "9");

  testOutput();
}
