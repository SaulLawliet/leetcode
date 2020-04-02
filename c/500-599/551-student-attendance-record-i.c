/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 第一次提交的时候才发现又审错题了, Late 是连续3次, 而不是总共3次.
 */

#include <stdbool.h>
#include "c/test.h"

bool checkRecord(char *s) {
  int a = 0, l = 0;
  while (*s != '\0') {
    if (*s == 'L') {
      if (++l > 2) return false;
    } else {
      l = 0;
    }

    if (*s == 'A') {
      if (++a > 1) return false;
    }

    s++;
  }
  return true;
}

void test(bool expect, char *s) {
  EXPECT_EQ_INT(expect, checkRecord(s));
}

int main(void) {
  test(true, "PPALLP");
  test(false, "PPALLL");

  return testOutput();
}
