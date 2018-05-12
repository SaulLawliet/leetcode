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
  testBinaryTreeRoundTrip("[1,2,3]", 2);
  testBinaryTreeRoundTrip("[1,null,2,3]", 3);
  testBinaryTreeRoundTrip("[5,4,7,3,null,2,null,-1,null,9]", 4);

  return testOutput();
}
