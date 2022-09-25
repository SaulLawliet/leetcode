/*
 * Copyright (C) 2022, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 跟 No.112, 一样的思路, 只是需要记录一下路径
 */

#include "c/data-structures/array.h"
#include "c/data-structures/binary-tree.h"
#include "c/test.h"

void backtracking(int **tmp, int tmpIndex, int ***returnArray, int *returnSize, int **returnColumnSizes, struct TreeNode *root, int targetSum) {
  if (root == NULL) return;

  (*tmp)[tmpIndex++] = root->val;

  if (!root->left && !root->right) {
    if (targetSum == root->val) {
      int *arr = malloc(sizeof(int) * tmpIndex);
      for (int i = 0; i < tmpIndex; i++)
        arr[i] = (*tmp)[i];
      (*returnColumnSizes)[*returnSize] = tmpIndex;
      (*returnArray)[*returnSize] = arr;
      (*returnSize)++;
    }
  }

  backtracking(tmp, tmpIndex, returnArray, returnSize, returnColumnSizes, root->left, targetSum - root->val);
  backtracking(tmp, tmpIndex, returnArray, returnSize, returnColumnSizes, root->right, targetSum - root->val);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **pathSum(struct TreeNode *root, int targetSum, int *returnSize, int **returnColumnSizes) {
  *returnSize = 0;
  int **returnArray = malloc(sizeof(int *) * 1000);  // 假设 1k 个
  *returnColumnSizes = malloc(sizeof(int) * 1000);

  // 拿到高度, 绝定动态数组长度
  int height = treeHeight(root);
  int *tmp = malloc(sizeof(int) * height);

  backtracking(&tmp, 0, &returnArray, returnSize, returnColumnSizes, root, targetSum);

  free(tmp);

  return returnArray;
}

void test(const char *expect, const char *rootStr, int targetSum) {
  struct TreeNode* root = treeParse(rootStr);

  int returnSize;
  int *returnColumnSizes;

  int **returnArray = pathSum(root, targetSum, &returnSize, &returnColumnSizes);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString2D(returnArray, returnSize, returnColumnSizes, ARRAY_INT));

  treeFree(root);
}

int main(void) {
  test("[[5,4,11,2],[5,8,4,5]]", "[5,4,8,11,null,13,4,7,2,null,null,5,1]", 22);

  return testOutput();
}
