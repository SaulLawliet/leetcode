/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.

 * v1: 先计算链表的长度, 把问题变成删除从头开始的第n个节点
 * v2: 维持两个链表(slow, fast)
 *     1. 先将 fast 后移n次
 *     2. 如果 fast 不是空, 同时后移 slowfast,
 *     直到 fast 为空时, slow 就是要删除的节点
 */

#include <stdlib.h>  /* free() */
#include "../test.h"
#include "../data-structures/linked-list.h"

int getLenght(struct ListNode* head) {
  int len = 0;
  while (head) {
    len++;
    head = head->next;
  }
  return len;
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeNthFromEnd_v1(struct ListNode* head, int n) {
  struct ListNode *p = head;
  int index = getLenght(head) - n - 1;  /* 要获取删除节点的上一个 */
  if (index == -1) {  /* 此时删除头节点 */
    head = head->next;
    free(p);
  } else {
    while (index--) {
      p = p->next;
    }
    struct ListNode *removeNode = p->next;
    p->next = removeNode->next;
    free(removeNode);
  }
  return head;
}

struct ListNode* removeNthFromEnd_v2(struct ListNode* head, int n) {
  struct ListNode *slow = head, *fast = head;
  while (n--) {
    fast = fast->next;
  }

  if (fast == NULL) {
    head = head->next;
    free(slow);
    return head;
  }

  while (fast->next != NULL) {
    slow = slow->next;
    fast = fast->next;
  }
  struct ListNode *removeNode = slow->next;
  slow->next = removeNode->next;
  free(removeNode);
  return head;
}

void test(const char* expect, const char* s, int n) {
  struct ListNode * head = NULL;

  head = removeNthFromEnd_v1(linkedlistNewByStr(s), n);
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, linkedlistToString(head));
  linkedlistFree(head);

  head = removeNthFromEnd_v2(linkedlistNewByStr(s), n);
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, linkedlistToString(head));
  linkedlistFree(head);
}

int main(void) {
  test("1 -> 2 -> 3 -> 4", "1 -> 2 -> 3 -> 4 -> 5", 1);
  test("1 -> 2 -> 3 -> 5", "1 -> 2 -> 3 -> 4 -> 5", 2);
  test("1 -> 2 -> 4 -> 5", "1 -> 2 -> 3 -> 4 -> 5", 3);
  test("1 -> 3 -> 4 -> 5", "1 -> 2 -> 3 -> 4 -> 5", 4);
  test("2 -> 3 -> 4 -> 5", "1 -> 2 -> 3 -> 4 -> 5", 5);

  return testOutput();
}
