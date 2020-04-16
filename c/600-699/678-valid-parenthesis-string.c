/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 看到括号匹配, 很容易想到用栈来解决
 * 由于'*'可以匹配任何字符串, 所以弹出的时候优先弹出'('
 * 最后尝试将剩余的'(', 用'*'来匹配
 */

#include <stdbool.h>
#include "c/test.h"

struct stack {
  int size;
  char data[100]; /* The string size will be in the range [1, 100] */
};

bool pop(struct stack *s) {
  if (s->size == 0) return false;
  /* 如果不为空, 一定能匹配到 */
  int i = s->size-- - 1;
  while (i != 0) {
    if (s->data[i] == '(') break; /* 优先匹配'(', 其次匹配'*' */
    i--;
  }
  s->data[i] = '*';
  return true;
}

void push(struct stack *s, int v) {
  s->data[s->size++] = v;
}

bool isValid(struct stack *s) {
  if (s->size > 0) {
    int n = 0;
    for (int i = s->size - 1; i >= 0; i--) {
      s->data[i] == '*' ? n++ : n--;
      if (n < 0) return false;
    }
  }

  return true;
}

bool checkValidString(char *s) {
  struct stack stack = {};
  while (*s != '\0') {
    if (*s != ')')
      push(&stack, *s);
    else if (!pop(&stack))
      return false;
    s++;
  }

  return isValid(&stack);
}

void test(bool expect, char *s) {
  EXPECT_EQ_INT(expect, checkValidString(s));
}

int main(void) {
  test(true, "()");
  test(true, "(*)");
  test(true, "(*))");

  test(true, "(*()");
  test(false, "(())((())()()(*)(*()(())())())()()((()())((()))(*");

  return testOutput();
}
