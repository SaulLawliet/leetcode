/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 如果快慢指针最后相遇, 则是循环链表
 */

#include <stdbool.h>
#include "c/data-structures/linked-list.h"
#include "c/test.h"

bool hasCycle(struct ListNode *head) {
  struct ListNode *fast = head, *slow = head;
  while (fast != NULL && fast->next != NULL && slow != NULL) {
    if ((fast = fast->next->next) == (slow = slow->next)) {
      return true;
    }
  }
  return false;
}

void test(bool expect, char *str, int pos) {
  struct ListNode *head = linkedlistParse(str);
  /* 构建循环链表, 之后解除 */
  struct ListNode *tail = head;
  while (tail->next)
    tail = tail->next;

  if (pos >= 0) {
    tail->next = head;
    for (int i = 0; i < pos; i++)
      tail->next = tail->next->next;
  }

  EXPECT_EQ_INT(expect, hasCycle(head));

  tail->next = NULL;
  linkedlistFree(head);
}

int main(void) {
  test(true, "[3,2,0,-4]", 1);
  test(true, "[1,2]", 0);
  test(false, "[1]", -1);

  return testOutput();
}
