/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include "c/data-structures/binary-tree.h"

#include <stdlib.h> /* NULL, atoi(), malloc(), free() */
#include <string.h> /* strcmp(), strlen(), strncpy() */
#include <stdio.h>  /* snprintf() */
#include <math.h>   /* pow() */

#include "c/data-structures/array.h"

#define TREE_NODE_NULL "null"

struct TreeNode *treeMakeByIndex(arrayEntry *e, int index) {
  int size = arraySize(e);
  if (index >= size) return NULL;

  char *str = ((char **)arrayValue(e))[index];
  if (strcmp(str, TREE_NODE_NULL) == 0) return NULL;

  struct TreeNode *tree = malloc(sizeof(struct TreeNode));
  tree->val = atoi(str);
  tree->left = treeMakeByIndex(e, index * 2 + 1);
  tree->right = treeMakeByIndex(e, index * 2 + 2);
  return tree;
}

void treeToArray(struct TreeNode *tree, char **array, int index) {
  if (tree == NULL) return;
  int size = snprintf(NULL, 0, "%d", tree->val) + 1;
  snprintf((array[index] = malloc(size)), size, "%d", tree->val);
  treeToArray(tree->left, array, index * 2 + 1);
  treeToArray(tree->right, array, index * 2 + 2);
}

struct TreeNode *treeParse(const char *str) {
  arrayEntry *e = arrayParse(str, ARRAY_STRING);
  struct TreeNode *tree = treeMakeByIndex(e, 0);
  arrayFree(e);
  return tree;
}

char *treeToString(struct TreeNode *tree) {
  int len = pow(2, treeHeight(tree)) - 1;
  char **array = malloc(sizeof(char *) * len);
  for (int i = 0; i < len; ++i) array[i] = NULL;

  treeToArray(tree, array, 0);

  while (array[len-1] == NULL) len--;

  int nullLen = strlen(TREE_NODE_NULL) + 1;
  for (int i = 0; i < len; ++i)
    if (array[i] == NULL)
      strncpy((array[i] = malloc(nullLen)), TREE_NODE_NULL, nullLen);

  return arrayToString1D(array, len, ARRAY_STRING);
}

void treeFree(struct TreeNode *tree) {
  if (tree == NULL) return;
  treeFree(tree->left);
  treeFree(tree->right);
  free(tree);
}

int treeHeight(struct TreeNode *tree) {
  if (tree == NULL) return 0;
  int leftHeight = treeHeight(tree->left);
  int rightHeight = treeHeight(tree->right);
  return leftHeight >= rightHeight ? leftHeight + 1 : rightHeight + 1;
}
