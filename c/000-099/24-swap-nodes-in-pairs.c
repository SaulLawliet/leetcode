/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 看到如此优雅的版本, 就不贴我那屎一样的代码, 虽然它也ac了...
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
struct ListNode* swapPairs(struct ListNode* head) {
  struct ListNode **p = &head, *a, *b;
  while ((a = *p) && (b = a->next)) {
    a->next = b->next;
    b->next = a;
    *p = b;
    p = &(a->next);
  }
  return head;
}

void test(const char* expect, const char* s) {
  struct ListNode* head = swapPairs(linkedlistNewByStr(s));
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, linkedlistToString(head));

  linkedlistFree(head);
}

int main(void) {
  test("2 -> 1 -> 4 -> 3", "1 -> 2 -> 3 -> 4");

  return testOutput();
}
