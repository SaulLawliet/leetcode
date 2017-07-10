/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include <stdlib.h>  /* NULL, free() */
#include <ctype.h>   /* isdigit() */
#include <stdio.h>   /* sprintf() */
#include "linked-list.h"
#include "../tools/stack.h"

struct ListNode* linkedlistNewByStr(const char* str) {
  struct ListNode* head = NULL;
  struct ListNode* node = NULL;

  char *end;
  while (*str != '\0') {
    if (node == NULL) {
      node = malloc(sizeof(struct ListNode));
      head = node;
    } else {
      node->next = malloc(sizeof(struct ListNode));
      node = node->next;
    }
    node->val = strtol(str, &end, 10);
    node->next = NULL;

    str = end;
    while (*str != '\0') {
      if (isdigit(*str) || (*str == '-' && isdigit(*(str+1)))) {
        break;
      }
      str++;
    }
  }

  return head;
}

char * linkedlistToString(struct ListNode *node) {
  context c = stackMake();
  if (node == NULL) {
    PUTC(&c, '\0');
    return c.stack;
  }

  int len;
  while (node != NULL) {
    /* INT32_MIN = -2147483648, len = 11
     * len(" -> ") = 4, total = 15 */
    len = sprintf(stackPush(&c, 15), "%d -> ", node->val);
    c.top -= 15 - len;
    node = node->next;
  }

  c.stack[c.top - 4] = '\0';
  return c.stack;
}

void linkedlistFree(struct ListNode *node) {
  struct ListNode *tmp;
  while (node != NULL) {
    tmp = node->next;
    free(node);
    node = tmp;
  }
}
