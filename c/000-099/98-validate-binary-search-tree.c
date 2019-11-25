/*
 * Copyright (C) 2019, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 按顺序访问节点, 每个节点均大于前一个节点即为有效
 */

#include <stdbool.h>
#include "c/data-structures/binary-tree.h"
#include "c/test.h"

bool isValid(struct TreeNode *node, struct TreeNode **prev) {
  if (node == NULL) return true;
  if (!isValid(node->left, prev)) return false;
  if (*prev != NULL && (*prev)->val >= node->val) return false;
  *prev = node;
  return isValid(node->right, prev);
}

bool isValidBST(struct TreeNode *root) {
  struct TreeNode *prev = NULL;
  return isValid(root, &prev);
}

void test(bool expect, const char *str) {
  struct TreeNode *root = treeParse(str);
  EXPECT_EQ_INT(expect, isValidBST(root));
  treeFree(root);
}

int main(void) {
  test(true, "[2,1,3]");
  test(false, "[5,1,4,null,null,3,6]");

  test(false, "[10,5,15,null,null,6,20]");
  test(true, "[2147483647]");
  test(true, "[-2147483648,null,2147483647]");
  test(false, "[1,2]");

  return testOutput();
}
