/*
 * Copyright (C) 2022, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 尝试用朴素方法, 排序之后, 从头开始处理, 移除头部, 二分查找double. 提交后超时...
 * 写下上句话的时候, 突然想出一个优化方法, 按“块”的二分查找
 *
 * ...
 *
 * 提交后依然失败, 看来只能换个思路了
 */

#include "c/data-structures/array.h"
#include "c/test.h"
#include "c/tools/compare.h"

/** [p, q], return index */
int binarySearch(int *arr, int p, int q, int target) {
  while (p <= q) {
    int mid = p + (q - p) / 2;
    if (target < arr[mid]) {
      q = mid - 1;
    } else if (target > arr[mid]) {
      p = mid + 1;
    } else {
      // 找到第一个的匹配
      if ((mid == 0) || (arr[mid - 1] != target))
        return mid;
      else
        q = mid - 1;
    }
  }
  return -1;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findOriginalArray(int *changed, int changedSize, int *returnSize) {
  *returnSize = 0;
  int *returnArray = malloc(sizeof(int) * (changedSize / 2));
  if (changedSize % 2 == 1) return returnArray;  // 长度是奇数, 一定不正确

  // 排好序, 方便处理
  qsort(changed, changedSize, sizeof(int), compare_ints);

  int skipHead = 0;  // 减少删除数组头部, 设置的变量

  while (changedSize - skipHead > 0) {
    int first = changed[skipHead];
    int countFirst = 0;
    while (skipHead + countFirst < changedSize && changed[skipHead + countFirst] == first) {
      countFirst++;
    }

    // 0 需要特殊处理一下
    int doubleIndex;
    if (first == 0 && countFirst % 2 == 0) {
      countFirst /= 2;
      doubleIndex = skipHead + countFirst;
    } else {
      doubleIndex = binarySearch(changed, skipHead + countFirst, changedSize - 1, first * 2);
      if (doubleIndex == -1) {
        // 如果找不到 double, 那么失败
        *returnSize = 0;
        return returnArray;
      }
    }


    for (int i = 0; i < countFirst; i++) {
      if (doubleIndex + i >= changedSize || changed[doubleIndex+i] != first * 2) {
        *returnSize = 0;
        return returnArray;
      }
      // 保存 original
      returnArray[(*returnSize)++] = first;
      skipHead++;
    }

    // 删除 double
    if (doubleIndex == skipHead) {
      skipHead += countFirst;  // 如果恰好是第一个, 那直接移动头部标识
    } else {
      changedSize -= countFirst;
      for (int i = doubleIndex; i < changedSize; i++) {
        changed[i] = changed[i + countFirst];
      }
    }
  }

  return returnArray;
}

void test(const char *expect, const char *charged) {
  arrayEntry *e = arrayParse1D(charged, ARRAY_INT);

  int returnSize;
  int *returnArray = findOriginalArray(arrayValue(e), arraySize(e), &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString1D(returnArray, returnSize, ARRAY_INT));

  arrayFree(e);
}

int main(void) {
  test("[1,3,4]", "[1,3,4,2,6,8]");
  test("[]", "[6,3,0,1]");
  test("[]", "[1]");

  test("[]", "[4,4]");
  test("[0,2]", "[0,4,2,0]");

  test("[0,0]", "[0,0,0,0]");
  test("[1,2,2,3,4,6]", "[1,2,3,2,4,6,2,4,6,4,8,12]");
  test("[]", "[1,4,2,1]");

  return testOutput();
}
