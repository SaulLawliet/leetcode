/*
 * Copyright (C) 2022, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 双指针往前跑即可
 * PS: Copilot 真的猛, 在函数内直接补全了, 试试看的态度提交到 leetcode 上, 竟然 AC 了, 当然最后把代码删掉重写的.
 */

#include <stdbool.h>
#include "c/test.h"

bool isSubsequence(char *s, char *t) {
  while (*s != '\0' && *t != '\0') {
    if (*s == *t) s++;
    t++;
  }
  return *s == '\0';
}

void test(bool expect, char *s, char *t) {
  EXPECT_EQ_INT(expect, isSubsequence(s, t));
}

int main(void) {
  test(true, "abc", "ahbgdc");
  test(false, "axc", "ahbgdc");

  return testOutput();
}
