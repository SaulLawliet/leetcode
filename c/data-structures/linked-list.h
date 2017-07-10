/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#ifndef __LINKED_LIST_H
#define __LINKED_LIST_H

struct ListNode {
  int val;
  struct ListNode *next;
};

/* STRING FORMAT: %d -> %d -> %d */
struct ListNode* linkedlistNewByStr(const char* str);
char * linkedlistToString(struct ListNode *node);
void linkedlistFree(struct ListNode *node);

#endif  /* __LINKED_LIST_H */
