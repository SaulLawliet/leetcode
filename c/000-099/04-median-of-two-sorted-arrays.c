/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 因为题目说了, 不使用额外空间. 所以基本要用指针来解决问题.
 * 整体思路就是, 比较两个数组的头, '删掉'较小的; 再比较两个数组的尾, '删掉'较大的. 如此反复
 * 补充: 当一个数组为空的时候, 中位数可以在另一个数组里直接计算出来
 */

#include <stdbool.h>
#include "../test.h"
#include "../data-structures/array.h"

/* 处理只有一个数组的情况 */
double findMedianInArray(int *nums, int size) {
  if (size == 0) return 0;
  int index = size >> 1;  // div 2
  if (size % 2 == 1) return nums[index];
  return (nums[index] + nums[index - 1]) / 2.0;
}

double findMedianSortedArrays(int* nums1, int nums1Size,
                              int* nums2, int nums2Size) {
  if (nums1Size == 0) return findMedianInArray(nums2, nums2Size);
  if (nums2Size == 0) return findMedianInArray(nums1, nums1Size);
  int *begin1 = nums1,
        *end1 = nums1 + nums1Size - 1,
      *begin2 = nums2,
        *end2 = nums2 + nums2Size - 1;

  bool flag = true;

  /* 某一个数组为空的时候 或 两个数组都只有一个元素, 停止循环 */
  while (begin1 <= end1 && begin2 <= end2 &&
         (begin1 != end1 || begin2 != end2)) {
    if (flag) {
      flag = false;
      *begin1 <= *begin2 ? begin1++ : begin2++;
    } else {
      flag = true;
      *end1 >= *end2 ? end1-- : end2--;
    }
  }

  /* 当 flag = false 时, 需要再处理一下'较大元素' (true=1, false=0) */
  if (begin1 > end1) return findMedianInArray(begin2, end2 - begin2 + flag);
  if (begin2 > end2) return findMedianInArray(begin1, end1 - begin1 + flag);

  if (!flag) return *begin1 <= *begin2 ? *begin1 : *begin2;
  return (*begin1 + *begin2) / 2.0;
}

void test(double expect, const char* s1, const char* s2) {
  int nums1Size, nums2Size;
  int *nums1 = arrayNewByStr(s1, &nums1Size);
  int *nums2 = arrayNewByStr(s2, &nums2Size);

  EXPECT_EQ_DOUBLE(expect, findMedianSortedArrays(nums1, nums1Size, nums2, nums2Size));

  free(nums1);
  free(nums2);
}

/*
  nums1 = [1, 3]
  nums2 = [2]
  The median is 2.0

  nums1 = [1, 2]
  nums2 = [3, 4]
  The median is (2 + 3)/2 = 2.5
 */
int main(void) {
  test(2.0, "[1, 3]", "[2]");
  test(2.5, "[1, 2]", "[3, 4]");

  return testOutput();
}
