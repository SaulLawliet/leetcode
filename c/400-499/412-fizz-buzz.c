/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 * 使用 snprintf 替代 itoa
 */

#include <stdio.h>  /* snprintf() */
#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* memcpy() */
#include "c/data-structures/array.h"
#include "c/test.h"

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **fizzBuzz(int n, int *returnSize) {
  *returnSize = n;
  char **rtn = malloc(sizeof(char*) * n);
  for (int i = 1; i <= n; i++) {  /* sizeof(char) == 1 */
    if (i % 15 == 0)     memcpy(rtn[i-1] = malloc(9), "FizzBuzz", 9);
    else if (i % 3 == 0) memcpy(rtn[i-1] = malloc(5), "Fizz", 5);
    else if (i % 5 == 0) memcpy(rtn[i-1] = malloc(5), "Buzz", 5);
    else                 snprintf(rtn[i-1] = malloc(i/10+2), i/10+2, "%d", i);
  }
  return rtn;
}

void test(const char *expect, int n) {
  int returnSize;
  char **a = fizzBuzz(n, &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString1D(a, returnSize, ARRAY_STRING));
}

int main(void) {
  test("[1,2,Fizz,4,Buzz,Fizz,7,8,Fizz,Buzz,11,Fizz,13,14,FizzBuzz,16]", 16);

  return testOutput();
}
