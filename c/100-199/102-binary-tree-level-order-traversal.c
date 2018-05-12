/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 提前分配好空间, 然后遍历树即可
 */

#include <math.h>   /* pow() */
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

void dfs(int ***rtn, int **columnSizes, struct TreeNode *root, int index) {
  if (root == NULL) return;
  (*rtn)[index][(*columnSizes)[index]++] = root->val;
  dfs(rtn, columnSizes, root->left, index+1);
  dfs(rtn, columnSizes, root->right, index+1);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **levelOrder(struct TreeNode *root, int **columnSizes, int *returnSize) {
  *returnSize = treeHeight(root);
  if (*returnSize <= 0) return NULL;

  // initialize
  int **rtn = malloc(sizeof(int *) * *returnSize);
  *columnSizes = malloc(sizeof(int) * *returnSize);
  for (int i = 0; i < *returnSize; ++i) {
    rtn[i] = malloc(sizeof(int) * pow(2, i < 8 ? i : 8)); /* 防止树的高度过大 */
    (*columnSizes)[i] = 0;
  }

  dfs(&rtn, columnSizes, root, 0);
  return rtn;
}

void test(const char *expect, const char *s) {
  struct TreeNode* tree = treeParse(s);
  int *columnSizes;
  int returnSize;
  int** rtn = levelOrder(tree, &columnSizes, &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString2D(rtn, returnSize, columnSizes, ARRAY_INT));

  treeFree(tree);
}

int main(void) {
  test("[[3],[9,20],[15,7]]", "[3,9,20,null,null,15,7]");

  return testOutput();
}
