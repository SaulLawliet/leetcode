/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 递归解法.
 * 找到第一个大于根结点的值, 前一半为左树, 右有一半为右树.
 */

#include <stdlib.h>
#include "c/data-structures/array.h"
#include "c/data-structures/binary-tree.h"
#include "c/test.h"

struct TreeNode *recursive(int *preorder, int i, int j) {
  if (i > j) return NULL;
  struct TreeNode *root = treeNewNode(preorder[i]);
  int mid = i;
  for (; mid <= j; mid++)
    if (preorder[mid] > root->val)
      break;
  root->left = recursive(preorder, i + 1, mid - 1);
  root->right = recursive(preorder, mid, j);
  return root;
}

struct TreeNode *bstFromPreorder(int *preorder, int preorderSize) {
  return recursive(preorder, 0, preorderSize - 1);
}

void test(const char *expect, char *s) {
  arrayEntry *e = arrayParse1D(s, ARRAY_INT);
  struct TreeNode *root = bstFromPreorder(arrayValue(e), arraySize(e));

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, treeToString(root));

  treeFree(root);
  arrayFree(e);
}

int main(void) {
  test("[8,5,10,1,7,null,12]", "[8,5,1,7,10,12]");

  return testOutput();
}
