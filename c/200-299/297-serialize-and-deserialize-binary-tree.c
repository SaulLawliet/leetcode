/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
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
/** Encodes a tree to a single string. */
char *serialize(struct TreeNode *root) {
  return treeToString(root);
}

/** Decodes your encoded data to tree. */
struct TreeNode *deserialize(char *data) {
  return treeParse(data);
}

// Your functions will be called as such:
// char* data = serialize(root);
// deserialize(data);

void test(char *data) {
  struct TreeNode *root = deserialize(data);
  char *actual = serialize(root);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(data, actual);

  treeFree(root);
}

int main(void) {
  test("[1,2,3,null,null,4,5]");

  // https://leetcode.com/faq/#binary-tree
  test("[]");
  test("[1,2,3]");
  test("[1,null,2,3]");
  test("[5,4,7,3,null,2,null,-1,null,9]");

  return testOutput();
}
