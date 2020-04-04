/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 两个指针向后移动即可
 */

#include <stdbool.h>
#include "c/test.h"

bool isLongPressedName(char *name, char *typed) {
  char *p1 = name, *p2 = typed;
  char last;

  while (*p1 || *p2) {
    if (*p1 == *p2) {
      last = *p1++;
    } else if (*p2 != last) {
      return false;
    }
    p2++;
  }
  return true;
}

void test(bool expect, char *name, char *typed) {
  EXPECT_EQ_INT(expect, isLongPressedName(name, typed));
}

int main(void) {
  test(true, "alex", "aaleex");
  test(false, "saeed", "ssaaedd");
  test(true, "leelee", "lleeelee");
  test(true, "laiden", "laiden");

  return testOutput();
}
