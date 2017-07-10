/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 第一次提交的时候, 以为 k > 0 && k < len(head)
 * 实际上, k 可以是任意的正整数
 */

#include <stdlib.h> /* NULL */
#include "../test.h"
#include "../data-structures/linked-list.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* rotateRight(struct ListNode* head, int k) {
  if (!k || !head) return head;
  struct ListNode *b = head;
  int i = k;

  while (i) {
    if (!b) {
      i %= (k-i);  /* 优化 k 远大于 len(head) 的情况 */
      if (!i) break;
      b = head;
    }
    b = b->next;
    i--;
  }
  if (!b) return head;

  struct ListNode *a = head, *rt;
  while (b->next) {
    a = a->next;
    b = b->next;
  }
  rt = a->next;
  a->next = NULL;
  b->next = head;
  return rt;
}

void test(const char* expect, const char* s, int k) {
  struct ListNode* head = linkedlistNewByStr(s);
  head = rotateRight(head, k);
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, linkedlistToString(head));

  linkedlistFree(head);
}

int main(void) {
  test("4 -> 5 -> 1 -> 2 -> 3", "1 -> 2 -> 3 -> 4 -> 5", 2);
  test("4 -> 5 -> 1 -> 2 -> 3", "1 -> 2 -> 3 -> 4 -> 5", 12);
  test("2 -> 3 -> 4 -> 5 -> 1", "1 -> 2 -> 3 -> 4 -> 5", 4);

  return testOutput();
}
