/*
 * Copyright (C) 2019, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 后缀表达式, 维护一个存放数字的栈, 遇到数字放入, 遇到符号弹出, 即可.
 */

#include <stdlib.h> /* malloc(), atoi() */

#include "c/data-structures/array.h"
#include "c/test.h"

int evalRPN(char **tokens, int tokensSize) {
  int *stack = malloc(sizeof(int) * (tokensSize / 2 + 1));
  int top = 0;

  int n, a, b;
  for (int i = 0; i < tokensSize; i++) {
    char first = tokens[i][0];
    if (first == '+' || (first == '-' && !tokens[i][1]) || first == '*' || first == '/') {
      b = stack[--top];
      a = stack[--top];
      switch (first) {
        case '+': n = a + b; break;
        case '-': n = a - b; break;
        case '*': n = a * b; break;
        case '/': n = a / b; break;
      }
    } else {
      n = atoi(tokens[i]);
    }
    stack[top++] = n;
  }

  free(stack);

  return n;
}


void test(int expect, char *str) {
  arrayEntry *e = arrayParse1D(str, ARRAY_STRING);

  EXPECT_EQ_INT(expect, evalRPN(arrayValue(e), arraySize(e)));

  arrayFree(e);
}

int main(void) {
  test(9, "[2, 1, +, 3, *]");
  test(6, "[4, 13, 5, /, +]");
  test(22, "[10, 6, 9, 3, +, -11, *, /, *, 17, +, 5, +]");

  return testOutput();
}
