/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 想知道叶子之间的最大距离, 那么最终的结果一定是某个节点的左结点高度+右节点高度
 * 因此中间数据应该是当前节点的高度
 * 后序遍历, 同时维护一个最大距离
 */

#include "c/data-structures/binary-tree.h"
#include "c/test.h"

int walk(struct TreeNode *root, int *max) {
  if (root == NULL) {
    return 0;
  }

  int left = walk(root->left, max);
  int right = walk(root->right, max);

  if (*max < left + right) {
    *max = left + right;
  }
  return (left > right ? left : right) + 1;
}

int diameterOfBinaryTree(struct TreeNode *root) {
  int max = 0;
  walk(root, &max);
  return max;
}

void test(int expect, char *s) {
  struct TreeNode *root = treeParse(s);
  EXPECT_EQ_INT(expect, diameterOfBinaryTree(root));
  treeFree(root);
}

int main(void) {
  test(3, "[1,2,3,4,5]");

  test(5, "[1,2,3,4,5,null,6,null,null,7,8]");
  test(3, "[4,1,null,2,null,3]");

  return testOutput();
}
