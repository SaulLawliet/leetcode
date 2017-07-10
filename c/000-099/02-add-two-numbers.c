/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 题目就是两个正整数相加, 链表的顺序是数字的低位到高位.
 * 两个注意点:
 *   1: 链表长度不一致
 *   2: 进位
 */

#include <stdlib.h>  /* NULL, malloc() */
#include "../test.h"
#include "../data-structures/linked-list.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
  struct ListNode *r = NULL, *lastNode = NULL;
  int carry = 0;
  while (l1 || l2) {
    if (!r) {  // first node.
      lastNode = r = malloc(sizeof(struct ListNode));
    } else {
      lastNode->next = malloc(sizeof(struct ListNode));
      lastNode = lastNode->next;
    }

    int val1 = 0, val2 = 0;
    if (l1) {
      val1 = l1->val;
      l1 = l1->next;
    }

    if (l2) {
      val2 = l2->val;
      l2 = l2->next;
    }

    int val = val1 + val2 + carry;
    if (val > 9) {
      carry = 1;
      val -= 10;
    } else {
      carry = 0;
    }
    lastNode->val = val;
    lastNode->next = NULL;  /* NOTE: 失败多次的原因竟然是没写这一行 */
  }

  if (carry > 0) {  /* 处理最后进位的情况 */
    lastNode->next = malloc(sizeof(struct ListNode));
    lastNode->next->val = carry;
    lastNode->next->next = NULL;
  }
  return r;
}

void test(const char* s1, const char* s2, const char* expect) {
  struct ListNode* l1 = linkedlistNewByStr(s1);
  struct ListNode* l2 = linkedlistNewByStr(s2);
  struct ListNode* actual = addTwoNumbers(l1, l2);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, linkedlistToString(actual));

  linkedlistFree(l1);
  linkedlistFree(l2);
  linkedlistFree(actual);
}

/*
  Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
  Output: 7 -> 0 -> 8
 */
int main(void) {
  test("2 -> 4 -> 3", "5 -> 6 -> 4", "7 -> 0 -> 8");

  return testOutput();
}
