/*
 * Copyright (C) 2023, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 前序遍历二叉树, 计算最小差值即可
 */

#include "c/data-structures/binary-tree.h"
#include "c/test.h"

void walk(struct TreeNode *root, int *lastVal, int *min) {
  if (root->left) walk(root->left, lastVal, min);
  if (*lastVal >= 0) {
    int minus = root->val - *lastVal;
    if (*min > minus) {
      *min = minus;
    }
  }
  *lastVal = root->val;
  if (root->right) walk(root->right, lastVal, min);
}

int getMinimumDifference(struct TreeNode *root) {
  // 0 <= Node.val <= 10^5
  int lastVal = -1;
  int min = 100000 + 1;

  walk(root, &lastVal, &min);

  return min;
}

void test(int expect, char *str) {
  struct TreeNode *root = treeParse(str);
  EXPECT_EQ_INT(expect, getMinimumDifference(root));
  treeFree(root);
}

int main(void) {
  test(1, "[4,2,6,1,3]");
  test(1, "[1,0,48,null,null,12,49]");

  return testOutput();
}
