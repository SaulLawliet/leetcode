/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 经过了 21 和 24 之后, 算是学会了 'pointer-pointer' 的写法
 */

#include "../test.h"
#include "../data-structures/linked-list.h"

/**
  * Definition for singly-linked list.
  * struct ListNode {
  *     int val;
  *     struct ListNode *next;
  * };
  */
struct ListNode* deleteDuplicates(struct ListNode* head) {
  struct ListNode **p = &head, *a, *b;
  while ((a = *p)) {
    while ((b = a->next) && a->val == b->val) {
      a->next = b->next;
      free(b);
    }
    p = &((*p)->next);
  }
  return head;
}

void test(const char* expect, const char* s) {
  struct ListNode* head = deleteDuplicates(linkedlistNewByStr(s));
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, linkedlistToString(head));

  linkedlistFree(head);
}

/*
  Given 1->1->2, return 1->2.
  Given 1->1->2->3->3, return 1->2->3.
 */
int main(void) {
  test("1 -> 2", "1 -> 1 -> 2");
  test("1 -> 2 -> 3", "1 -> 1 -> 2 -> 3 -> 3");

  return testOutput();
}
