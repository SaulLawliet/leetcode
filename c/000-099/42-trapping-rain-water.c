/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 维持首尾两个指针, 和首尾的最大高度, 然后向中间寻找
 * 如果遇到'坑', 就把'坑'的深度累加到结果中
 */

#include "../test.h"
#include "../data-structures/array.h"

int trap(int* height, int heightSize) {
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

void test(const char* str, int except) {
  size_t heightSize;
  int* height = arrayNewByStr(str, &heightSize);

  EXPECT_EQ_INT(except, trap(height, heightSize));
  free(height);
}

int main(void) {
  test("[0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]", 6);

  return testOutput();
}
