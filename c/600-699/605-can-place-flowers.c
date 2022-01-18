/*
 * Copyright (C) 2022, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 看似很简单的一道题, 但也挺有趣的, 因为靠边的时候规则是特殊的!
 */

#include <stdbool.h>
#include "c/data-structures/array.h"
#include "c/test.h"

bool canPlaceFlowers(int *flowerbed, int flowerbedSize, int n) {
  int count = 1;  // 开头的边界额外奖励一个, 方便循环代码计算
  for (int i = 0; i < flowerbedSize; i++) {
    if (flowerbed[i] == 0) {
      count++;
    } else if (count > 0) {
      n -= (count - 1) / 2;
      count = 0;
    }
  }

  // 结尾的边界更改一下计算的规则即可
  return (n - count / 2) <= 0;
}

void test(bool expect, const char *flowerbed, int n) {
  arrayEntry *e = arrayParse1D(flowerbed, ARRAY_INT);
  EXPECT_EQ_INT(expect, canPlaceFlowers(arrayValue(e), arraySize(e), n));
  arrayFree(e);
}

int main(void) {
  // 示例
  test(true, "[1,0,0,0,1]", 1);
  test(false, "[1,0,0,0,1]", 2);

  // 提交出错
  test(false, "[1,0,0,0,0,1]", 2);
  test(true, "[0,0,1,0,1]", 1);
  return testOutput();
}
