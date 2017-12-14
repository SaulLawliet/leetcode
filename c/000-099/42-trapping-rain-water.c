/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 维持首尾两个指针, 和首尾的最大高度, 然后向中间寻找
 * 如果遇到'坑', 就把'坑'的深度累加到结果中
 */

#include "../test.h"
#include "../data-structures/array.h"

int trap(int *height, int heightSize) {
  int rtn = 0,
    left_max = 0, right_max = 0,
    left = 0, right = heightSize - 1;

  while (left < right) {
    if (height[left] < height[right]) {
      height[left] >= left_max ? (left_max = height[left]) : (rtn += left_max - height[left]);
      ++left;
    } else {
      height[right] >= right_max ? (right_max = height[right]) : (rtn += right_max - height[right]);
      --right;
    }
  }
  return rtn;
}

void test(int expect, const char *str) {
  arrayEntry *e = arrayParse(str, ARRAY_INT);

  EXPECT_EQ_INT(expect, trap(arrayValue(e), (arraySize(e))));

  arrayFree(e);
}

int main(void) {
  test(6, "[0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]");

  return testOutput();
}
