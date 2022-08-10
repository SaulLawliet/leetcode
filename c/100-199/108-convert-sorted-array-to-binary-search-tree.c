/*
 * Copyright (C) 2022, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 有序数组 转成 二叉搜索树? 用递归
 */

#include <stdlib.h> /* malloc() */
#include "c/data-structures/array.h"
#include "c/data-structures/binary-tree.h"
#include "c/test.h"

struct TreeNode *toBST(int *nums, int p, int q) {
  if (p >= q) return NULL;

  int mid = (p + q) / 2;
  struct TreeNode *node = malloc(sizeof(struct TreeNode));
  node->val = nums[mid];
  node->left = toBST(nums, p, mid);
  node->right = toBST(nums, mid+1, q);
  return node;
}

struct TreeNode *sortedArrayToBST(int *nums, int numsSize) {
  return toBST(nums, 0, numsSize);
}

void test(const char *expect, const char *nums) {
  arrayEntry *e = arrayParse1D(nums, ARRAY_INT);
  struct TreeNode *t = sortedArrayToBST(arrayValue(e), arraySize(e));

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, treeToString(t));

  arrayFree(e);
  treeFree(t);
}

int main(void) {
  test("[0,-3,9,-10,null,5]", "[-10,-3,0,5,9]");
  test("[3,1]", "[1,3]");

  return testOutput();
}
