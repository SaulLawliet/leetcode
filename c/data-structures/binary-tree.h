/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#ifndef DATA_STRUCTURES_BINARY_TREE_H_
#define DATA_STRUCTURES_BINARY_TREE_H_

struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

struct TreeNode *treeParse(const char *str);
char *treeToString(struct TreeNode *tree);
void treeFree(struct TreeNode *tree);

int treeHeight(struct TreeNode *tree);

#endif /* DATA_STRUCTURES_BINARY_TREE_H_ */
