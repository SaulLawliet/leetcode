
/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 递归解就可以了
 */

#include "../test.h"
#include "../data-structures/array.h"

#define MAX_SIZE 20

void loop(char **rtn, int *returnSize, char *s, int *a, int i) {
  if (i > 3) {
    if (*s == '\0')
      sprintf((rtn[(*returnSize)++] = malloc(sizeof(char) * 16)),  /* xxx.xxx.xxx.xxx\0 */
              "%d.%d.%d.%d", a[0], a[1], a[2], a[3]);
    return;
  }
  int x = 0;
  char *p = s;
  while (*p) {
    x = x * 10 + (*p++ - '0');
    if (x <= 255) {
      a[i] = x;
      loop(rtn, returnSize, p, a, i+1);
    }
    if (x == 0 || x > 255) break;
  }
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **restoreIpAddresses(char *s, int *returnSize) {
  int *a = malloc(sizeof(int) * 4);
  char **rtn = malloc(sizeof(char*) * MAX_SIZE);
  *returnSize = 0;
  loop(rtn, returnSize, s, a, 0);
  free(a);
  return rtn;
}

void test(const char *expect, char *s) {
  int returnSize;
  char **a = restoreIpAddresses(s, &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString1D(a, returnSize, ARRAY_STRING));
}

int main(void) {
  test("[255.255.11.135,255.255.111.35]", "25525511135");
  test("[]", "00003");

  return testOutput();
}
