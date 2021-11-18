/*
 * Copyright (C) 2021, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 题目要求不使用额外的空间, 那么一定是利用原空间移动数字
 * 提交后, 排名很中庸
 * 查看了一下其他人的答案
 * 速度最快: 分配新的数组, 然后用旧的数据填空, 最后移动想到的内容到数组的前面
 * 内存最少: 返回的数组使用输入的数组(但应该是不符合规定吧?)
 */

#include "c/data-structures/array.h"
#include "c/test.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findDisappearedNumbers(int *nums, int numsSize, int *returnSize) {
  int c = 0;
  for (int i = 0; i < numsSize; ++i) {
    while (nums[i] != 0 && nums[i] != i + 1) {
      if (nums[i] == nums[nums[i] - 1]) {
        nums[i] = 0;
        ++c;
      } else {
        int tmp = nums[nums[i] - 1];
        nums[nums[i] - 1] = nums[i];
        nums[i] = tmp;
      }
    }
  }
  *returnSize = 0;
  int *rtn = malloc(sizeof(int) * c);
  for (int i = 0; i < numsSize; ++i) {
    if (nums[i] == 0) {
      rtn[(*returnSize)++] = i + 1;
    }
  }
  return rtn;
}

void test(const char *expect, const char *str) {
  arrayEntry *e = arrayParse1D(str, ARRAY_INT);
  int returnSize;
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString1D(findDisappearedNumbers(arrayValue(e), arraySize(e), &returnSize), returnSize, ARRAY_INT));
  arrayFree(e);
}

int main(void) {
  test("[5,6]", "[4,3,2,7,8,2,3,1]");
  test("[2]", "[1,1]");

  return testOutput();
}
