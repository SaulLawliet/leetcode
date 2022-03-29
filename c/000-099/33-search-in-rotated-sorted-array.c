/*
 * Copyright (C) 2017-2022, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * https://leetcode.com/problems/search-in-rotated-sorted-array/
 * Q: 在一个循环有序数组中(想象一个循环链表, 但起始位置可能不在数组头部), O(log n)的时间复杂度找到一个元素的位置
 *
 * 看到题目, 就是要实现一个升级版本的二分查找, 接下来就要考虑如何计算 low 和 high
 * 第1步: 判断哪边是有序的
 * 第2步: 找出异常情况: 要找的值在边界之外
 *
 * 修改记录:
 *   2022-03-28: 今天才发现, 之前没按规则实现, 于是重写了
 *   2017-08-25: 按照顺序查找实现的, 虽然AC并且耗时也是第一梯队的, 但代码不符合规则
 */

#include "c/data-structures/array.h"
#include "c/test.h"

int search(int *nums, int numsSize, int target) {
  int low = 0, high = numsSize - 1, mid;
  while (low <= high) {
    mid = (low + high) / 2;
    if (nums[mid] == target)
      return mid;

    if (nums[low] <= nums[mid]) {  // 左侧有序
      if (nums[mid] > target) {  // 可能在左边
        // 但特殊情况在右边
        if (nums[low] > target)
          low = mid + 1;
        else
          high = mid - 1;
      } else {
        low = mid + 1;
      }
    } else {  // 右侧有序
      if (nums[mid] < target) {  // 可能在右边
        // 但特殊情况在左边
        if (nums[high] < target)
          high = mid - 1;
        else
          low = mid + 1;
      } else {
        high = mid - 1;
      }
    }
  }
  return -1;
}

void test(int expect, const char *nums, int target) {
  arrayEntry *e = arrayParse1D(nums, ARRAY_INT);

  EXPECT_EQ_INT(expect, search(arrayValue(e), arraySize(e), target));

  arrayFree(e);
}

int main(void) {
  test(4, "[4,5,6,7,0,1,2]", 0);
  test(-1, "[4,5,6,7,0,1,2]", 3);
  test(-1, "[1]", 0);

  // 以下是提交错误时的测试用例
  test(0, "[3,5,1]", 3);
  test(2, "[5,1,3]", 3);
  test(0, "[5,1,3]", 5);
  test(4, "[4,5,6,7,8,1,2,3]", 8);
  test(1, "[3,1]", 1);

  return testOutput();
}
