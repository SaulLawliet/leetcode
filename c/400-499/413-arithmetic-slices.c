/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 只要知道最长的一段, 通过计算就可以知道这段有几个'片'
 * 长度 -> 数量
 *  3  ->  1
 *  4  ->  3
 *  5  ->  6
 *  6  ->  10
 *     ...
 * 最后把他们累加起来
 */

#include "c/data-structures/array.h"
#include "c/test.h"

int doMath(int count) {
  if (count < 2) return 0;
  return count * (count - 1) / 2;
}

int numberOfArithmeticSlices(int *A, int ASize) {
  if (ASize < 3) return 0;

  int rt = 0, count = 1;
  int flag = A[1] - A[0];
  for (int i = 2; i != ASize; i++) {
    int tmp = A[i] - A[i-1];
    if (tmp == flag) {
      ++count;
    } else {
      rt += doMath(count);
      flag = tmp;
      count = 1;
    }
  }
  return rt + doMath(count);
}

void test(int expect, const char *str) {
  arrayEntry *e = arrayParse1D(str, ARRAY_INT);

  EXPECT_EQ_INT(expect, numberOfArithmeticSlices(arrayValue(e), arraySize(e)));

  arrayFree(e);
}

int main(void) {
  test(3, "[1,2,3,4]");

  return testOutput();
}
