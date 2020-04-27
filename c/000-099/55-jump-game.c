/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 标记一个不可达的计数, 从后向前查找, 找不到加1, 找到置0, 最后判断计数是否等于0
 */

#include <stdbool.h>
#include "c/data-structures/array.h"
#include "c/test.h"

bool canJump(int *nums, int numsSize) {
  int flag = 0;
  for (int i = numsSize - 2; i >= 0; i--) {
    flag = nums[i] <= flag ? flag + 1 : 0;
  }

  return flag == 0;
}

void test(bool expect, char *s) {
  arrayEntry *e = arrayParse1D(s, ARRAY_INT);

  EXPECT_EQ_INT(expect, canJump(arrayValue(e), arraySize(e)));

  arrayFree(e);
}

int main(void) {
  test(true, "[2,3,1,1,4]");
  test(false, "[3,2,1,0,4]");

  test(true, "[0]");
  test(true, "[3,0,0,0]");
  test(false, "[1,1,0,1]");

  return testOutput();
}
