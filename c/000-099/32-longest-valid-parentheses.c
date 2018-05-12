/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 记录括号的索引到栈中, 同时弹出合法的括号索引.
 * 最后栈内都是非法括号的索引, 此时连续索引之间最大的差值就是答案.
 */

#include <assert.h> /* assert() */
#include <stdbool.h>
#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* strlen() */
#include "c/test.h"

struct StackRecord{
  int top;
  int *array;
};
typedef struct StackRecord * stack;

stack createEmptyStack(int len) {
  stack s = malloc(sizeof(struct StackRecord));
  s->array = malloc(sizeof(int) * len);
  s->top = -1;
  return s;
}

void freeStack(stack s) {
  free(s->array);
  free(s);
}

void push(stack s, int v) {
  s->array[++s->top] = v;
}

int pop(stack s) {
  assert(s->top > -1);
  return s->array[s->top--];
}

bool isEmpty(stack s) {
  return s->top == -1;
}

int top(stack s) {
  return s->array[s->top];
}

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
int longestValidParentheses(char* s) {
  int len = strlen(s);

  stack stack = createEmptyStack(len);
  for (int i = 0; i < len; i++) {
    if (s[i] == '(') {
      push(stack, i);
    } else {
      if (!isEmpty(stack) && s[top(stack)] == '(') pop(stack);
      else push(stack, i);
    }
  }
  int longest = 0;
  if (isEmpty(stack)) {
    longest = len;
  } else {
    int a = len, b;
    while (!isEmpty(stack)) {
      b = pop(stack);
      longest = MAX(longest, a-b-1);
      a = b;
    }
    longest = MAX(longest, a);
  }
  freeStack(stack);
  return longest;
}

void test(int expect, char* s) {
  EXPECT_EQ_INT(expect, longestValidParentheses(s));
}

int main(void) {
  test(2, "(()");
  test(4, ")()())");
  test(2, "()(()");
  test(2, "(()(((()");

  return testOutput();
}
