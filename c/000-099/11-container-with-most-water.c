/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 装水面积 = 两个竖线的距离 x 较短竖线的长度
 * 所以从两头往中间找最大的装水面积
 */

#include "../test.h"
#include "../data-structures/array.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
int maxArea(int* height, int heightSize) {
  int i = 0,
      j = heightSize - 1,
     rt = 0;

  while (i < j) {
    rt = MAX(rt, (j - i) * MIN(height[i], height[j]));
    height[i] <= height[j] ? i++ : j--;
  }

  return rt;
}

void test(int expect, const char* s) {
  int size;
  int *height = arrayNewByStr(s, &size);
  EXPECT_EQ_INT(expect, maxArea(height, size));

  free(height);
}

int main(void) {
  test(1, "[1, 1]");
  test(0, "[0, 2]");

  return testOutput();
}
