/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 首先 BST 的前序遍历是有序的, 然后二分查找的思路
 */

#include "c/data-structures/binary-tree.h"
#include "c/test.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int kthSmallest(struct TreeNode *root, int k) {
  int count = treeCount(root->left) + 1;
  if (count > k) {
    return kthSmallest(root->left, k);
  } else if (count < k) {
    return kthSmallest(root->right, k - count);
  } else {
    return root->val;
  }
}

void test(int expect, const char *str, int k) {
  struct TreeNode *root = treeParse(str);

  EXPECT_EQ_INT(expect, kthSmallest(root, k));

  treeFree(root);
}

int main(void) {
  test(1, "[3,1,4,null,2]", 1);
  test(3, "[5,3,6,2,4,null,null,1]", 3);

  testOutput();
}
