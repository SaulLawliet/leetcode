/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 树的根节点是 preorder[0],
 * 在 inorder 中找到等于 preorder[0] 值的位置,
 * 然后左侧即左树, 右侧即右树,
 * 如此反复.
 */

#include <assert.h> /* assert() */
#include <stdlib.h> /* malloc() */

#include "c/data-structures/array.h"
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
struct TreeNode *buildTree(int *preorder, int preorderSize, int *inorder, int inorderSize) {
  assert(preorderSize == inorderSize);
  int size = preorderSize;

  if (!size)return NULL;

  struct TreeNode *root = malloc(sizeof(struct TreeNode));
  root->val = preorder[0];
  if (size == 1) {
    root->left = NULL;
    root->right = NULL;
  } else {
    int index = -1;
    for (int i = 0; i < size; ++i) {
      if (inorder[i] == root->val) {
        index = i;
        break;
      }
    }
    root->left = buildTree(preorder + 1, index,
                           inorder, index);
    root->right = buildTree(preorder + 1 + index, size - 1 - index,
                            inorder + 1 + index, size - 1 - index);
  }
  return root;
}

void test(const char *expect, const char *preorderStr, const char *inorderStr) {
  arrayEntry *preorder = arrayParse(preorderStr, ARRAY_INT);
  arrayEntry *inorder = arrayParse(inorderStr, ARRAY_INT);
  struct TreeNode *tree = buildTree(arrayValue(preorder), arraySize(preorder),
                                    arrayValue(inorder), arraySize(inorder));

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, treeToString(tree));

  treeFree(tree);
  arrayFree(preorder);
  arrayFree(inorder);
}

int main(void) {
  test("[3,9,20,null,null,15,7]",
       "[3,9,20,15,7]",
       "[9,3,15,20,7]");

  test("[4,1,null,null,2,null,3]",
       "[4,1,2,3]",
       "[1,2,3,4]");

  testOutput();
}
