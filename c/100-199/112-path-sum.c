/*
 * Copyright (C) 2022, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 递归思想即可, 注意只要叶子才算数
 */

#include <stdbool.h>
#include "c/data-structures/binary-tree.h"
#include "c/test.h"

bool hasPathSum(struct TreeNode *root, int targetSum) {
  if (root == NULL) {
    return false;
  }

  if (!root->left && !root->right) {
    return targetSum == root->val;
  }

  return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);
}

void test(bool expect, const char *rootStr, int targetSum) {
  struct TreeNode *root = treeParse(rootStr);

  EXPECT_EQ_INT(expect, hasPathSum(root, targetSum));

  treeFree(root);
}

int main(void) {
  test(true, "[5,4,8,11,null,13,4,7,2,null,null,null,1]", 22);
  test(false, "[1,2,3]", 5);
  test(false, "[]", 0);

  test(false, "[1,2]", 1);

  return testOutput();
}
