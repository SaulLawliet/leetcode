/*
 * Copyright (C) 2022, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 思路跟108一样: 区别在于用“快慢指针”取中间节点
 */

#include "c/data-structures/binary-tree.h"
#include "c/data-structures/linked-list.h"
#include "c/test.h"

struct TreeNode *toBST(struct ListNode *head, struct ListNode *tail) {
  if (head == tail) return NULL;

  struct ListNode *slow = head;
  struct ListNode *fast = head;
  while (fast && fast != tail && fast->next && fast->next != tail) {
    slow = slow->next;
    fast = fast->next->next;
  }

  struct TreeNode *node = malloc(sizeof(struct TreeNode));
  node->val = slow->val;
  node->left = toBST(head, slow);
  node->right = toBST(slow->next, tail);
  return node;
}

struct TreeNode *sortedListToBST(struct ListNode *head) {
  return toBST(head, NULL);
}

void test(const char *expect, const char *nums) {
  struct ListNode *list = linkedlistParse(nums);
  struct TreeNode *tree = sortedListToBST(list);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, treeToString(tree));

  treeFree(tree);
  linkedlistFree(list);
}

int main(void) {
  test("[0,-3,9,-10,null,5]", "[-10,-3,0,5,9]");
  test("[]", "[]");
  test("[4,2,6,1,3,5,7,0]", "[0,1,2,3,4,5,6,7]");

  return testOutput();
}
