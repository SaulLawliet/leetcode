/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 维护一个栈, 模拟递归行为, 具体见代码
 */

#include <stdbool.h>
#include <stdlib.h>
#include "c/data-structures/array.h"
#include "c/data-structures/binary-tree.h"
#include "c/test.h"

#define MAX_SIZE 1000 /* 题目没有给出最大数量, 假设1000 */
struct stack {
  struct TreeNode *arr[MAX_SIZE];
  int size;
};

bool isEmpty(struct stack *s) {
  return s->size == 0;
}

void push(struct stack *s, struct TreeNode *node) {
  s->arr[s->size++] = node;
}

struct TreeNode *pop(struct stack *s) {
  if (s->size == 0) return NULL;
  return s->arr[--s->size];
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *inorderTraversal(struct TreeNode *root, int *returnSize) {
  int *rtn = malloc(sizeof(int) * MAX_SIZE);
  *returnSize = 0;

  struct stack s = {};
  struct TreeNode *cur = root;

  while (cur != NULL || !isEmpty(&s)) {
    while (cur != NULL) {
      push(&s, cur);
      cur = cur->left;
    }

    cur = pop(&s);
    rtn[(*returnSize)++] = cur->val;
    cur = cur->right;
  }

  return rtn;
}

void test(const char *expect, const char *s) {
  struct TreeNode *root = treeParse(s);
  int returnSize;
  int *rtn = inorderTraversal(root, &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString1D(rtn, returnSize, ARRAY_INT));

  treeFree(root);
}

int main(void) {
  test("[1,3,2]", "[1,null,2,3]");

  return testOutput();
}
