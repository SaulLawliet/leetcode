/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include "c/data-structures/binary-tree.h"
#include "c/test.h"

void testBinaryTreeRoundTrip(const char *str, int height) {
  struct TreeNode *tree = treeParse(str);

  EXPECT_EQ_INT(height, treeHeight(tree));
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(str, treeToString(tree));

  treeFree(tree);
}

int main(void) {
  testBinaryTreeRoundTrip("[]", 0);
  testBinaryTreeRoundTrip("[1]", 1);
  testBinaryTreeRoundTrip("[1,2,3,null,5,6]", 3);
  testBinaryTreeRoundTrip("[1,null,3,null,null,null,7]", 3);

  return testOutput();
}
