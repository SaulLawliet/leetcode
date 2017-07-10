/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 使用 stack, 即可轻松解决
 */

#include <stdlib.h>  /* malloc(), free() */
#include <string.h>  /* strlen() */
#include <assert.h>  /* assert() */
#include <stdbool.h>
#include "../test.h"

struct StackRecord{
  int top;
  char *array;
};
typedef struct StackRecord * stack;

stack createEmptyStack(int len) {
  stack s = malloc(sizeof(struct StackRecord));
  s->array = malloc(sizeof(char) * len);
  s->top = -1;
  return s;
}

void push(stack s, char v) {
  s->array[++s->top] = v;
}

char pop(stack s) {
  assert(s->top > -1);
  return s->array[s->top--];
}

bool isEmpty(stack s) {
  return s->top == -1;
}

bool isValid(char* s) {
  bool rt = true;
  stack stack = createEmptyStack(strlen(s));
  while (*s) {
    if (*s == '(') push(stack, ')');
    else if (*s == '{') push(stack, '}');
    else if (*s == '[') push(stack, ']');
    else {
      if (isEmpty(stack) || pop(stack) != *s) {
        rt = false;
        break;
      }
    }
    s++;
  }

  if (rt) rt = isEmpty(stack);
  free(stack->array);
  free(stack);
  return rt;
}

void test(bool expect, char* s) {
  EXPECT_EQ_INT(expect, isValid(s));
}

int main(void) {
  test(true, "()");
  test(true, "(){}[]");

  test(false, "(]");
  test(false, "([)]");
  test(false, "[");

  return testOutput();
}
