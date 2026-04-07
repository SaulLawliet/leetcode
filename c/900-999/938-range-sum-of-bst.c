/*
 * Copyright (C) 2023, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * https://leetcode.com/problems/range-sum-of-bst
 * 简单题目递归思路
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
int rangeSumBST(struct TreeNode* root, int low, int high) {
  if (root == NULL) return 0;

  int sum = 0;
  if (low <= root->val && root->val <= high) {
    sum += root->val;
  }
  if (low < root->val) {
    sum += rangeSumBST(root->left, low, high);
  }
  if (root->val < high) {
    sum += rangeSumBST(root->right, low, high);
  }
  return sum;
}

void test(const char* s, int low, int hight, int expect) {
  struct TreeNode* root = treeParse(s);
  int actual = rangeSumBST(root, low, hight);

  EXPECT_EQ_INT(expect, actual);

  treeFree(root);
}

int main(void) {
  test("[10,5,15,3,7,null,18]", 7, 15, 32);
  test("[10,5,15,3,7,13,18,1,null,6]", 6, 10, 23);

  return testOutput();
}
