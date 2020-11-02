/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include "c/data-structures/linked-list.h"
#include "c/test.h"

int getDecimalValue(struct ListNode *head) {
  int rtn = 0;
  while (head != NULL) {
    rtn <<= 1;
    rtn += head->val;
    head = head->next;
  }
  return rtn;
}

void test(int expect, const char *s) {
  struct ListNode *head = linkedlistParse(s);
  EXPECT_EQ_INT(expect, getDecimalValue(head));
  linkedlistFree(head);
}

int main(void) {
  test(5, "[1,0,1]");
  test(0, "[0]");
  test(1, "[1]");
  test(18880, "[1,0,0,1,0,0,1,1,1,0,0,0,0,0,0]");
  test(0, "[0,0]");

  return testOutput();
}
