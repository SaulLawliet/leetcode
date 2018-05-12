/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * v1: O(n^2)
 *     暴力计算, 两层循环
 * v2: O(n)
 *     这里的 Table 可以理解成 HashTable, Key 是字符, Value 是该字符最新的 Index.
 *     当字符的 Index 更改的时候, 计算出差值, 最大的一个差值就是结果.
 */

#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* strlen(), memset() */
#include "c/test.h"

int lengthOfLongestSubstring_v1(char *s) {
  int length = strlen(s);
  int i, j, len;

  int size = sizeof(char) * 128;
  char *table = malloc(size);
  int max = 1;

  for (i = 0; s[i] != '\0'; ++i) {
    if (i + max >= length) break;  /* 如果最大长度已经大于剩余长度, break */
    memset(table, 0, size);
    for (j = i, len = 0; s[j] != '\0'; ++j, ++len) {
      if (table[(int)s[j]] == 0) {
        table[(int)s[j]] = 1;
      } else {
        break;
      }
    }
    if (len > max) max = len;
  }

  free(table);
  return max;
}

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
int lengthOfLongestSubstring_v2(char* s) {
  int i = 0, j = 0, ans = 0, n = strlen(s);

  int size = sizeof(int) * 128;
  int *table = malloc(size);
  memset(table, 0, size);

  for (; j != n; j++) {
    i = MAX(i, table[(int)s[j]]);
    ans = MAX(ans, j + 1 - i);
    table[(int)s[j]] = j + 1;
  }

  free(table);
  return ans;
}

void test(int expect, char* s) {
  EXPECT_EQ_INT(expect, lengthOfLongestSubstring_v1(s));
  EXPECT_EQ_INT(expect, lengthOfLongestSubstring_v2(s));
}

/*
  Given "abcabcbb", the answer is "abc", which the length is 3.

  Given "bbbbb", the answer is "b", with the length of 1.

  Given "pwwkew", the answer is "wke", with the length of 3.
  Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
 */
int main(void) {
  test(3, "abcabcbb");
  test(1, "bbbbb");
  test(3, "pwwkew");

  return testOutput();
}
