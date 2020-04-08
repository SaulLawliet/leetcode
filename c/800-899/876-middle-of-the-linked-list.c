/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include "c/data-structures/linked-list.h"
#include "c/test.h"

struct ListNode *middleNode(struct ListNode *head) {
  struct ListNode *p1 = head, *p2 = head;

  while (p2 != NULL && p2->next != NULL) {
    p1 = p1->next;
    p2 = p2->next->next;
  }
  return p1;
}

void test(int expect, char *s) {
  struct ListNode *head = linkedlistParse(s);

  EXPECT_EQ_INT(expect, middleNode(head)->val);

  linkedlistFree(head);
}

int main(void) {
  test(3, "[1,2,3,4,5]");
  test(4, "[1,2,3,4,5,6]");

  return testOutput();
}
