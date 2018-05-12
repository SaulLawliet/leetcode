/*
 * Copyright (C) 2017-2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#ifndef C_DATA_STRUCTURES_LINKED_LIST_H_
#define C_DATA_STRUCTURES_LINKED_LIST_H_

struct ListNode {
  int val;
  struct ListNode *next;
};

struct ListNode *linkedlistParse(const char *str);
char *linkedlistToString(struct ListNode *list);
void linkedlistFree(struct ListNode *list);

int linkedlistLength(struct ListNode *list);

#endif /* C_DATA_STRUCTURES_LINKED_LIST_H_ */
