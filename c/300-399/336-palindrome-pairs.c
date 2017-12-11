/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 暴力计算, 比较耗时
 * TODO: 换个算法
 */

#include <string.h>  /* strlen() */
#include <stdbool.h>
#include "../test.h"
#include "../data-structures/array.h"

bool isPalindrome(const char* s1, const char* s2) {
  int l1 = strlen(s1), l2 = strlen(s2);
  for (int i = 0; i < (l1+l2)/2; ++i)
    if ((i < l1 ? s1[i] : s2[i-l1]) != (i < l2 ? s2[l2-i-1] : s1[l1-i+l2-1]))
      return false;

  return true;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** palindromePairs(char** words, int wordsSize, int** columnSizes, int* returnSize) {
  int** rt = malloc(sizeof(int*) * wordsSize * (wordsSize - 1));  /* 最多可能有 P(wordsSize, 2) 个 */

  int i, j, size = 0;
  for (i = 0; i < wordsSize; i++) {
    for (j = 0; j < wordsSize; j++) {
      if (i == j) continue;
      if (isPalindrome(words[i], words[j])) {
        rt[size] = malloc(sizeof(int) * 2);
        rt[size][0] = i;
        rt[size][1] = j;
        size++;
      }
    }
  }
  *returnSize = size;
  int *a = malloc(sizeof(int) * size);
  for(i = 0; i < size; i++)
    a[i] = 2;
  *columnSizes = a;
  return rt;
}

void test(const char* expect, const char* s) {
  int wordsSize;
  char** words = sarrayNewByStr(s, &wordsSize);

  int *columnSizes;
  int actualSize;
  int** actual = palindromePairs(words, wordsSize, &columnSizes, &actualSize);

  for (int i = 0; i < actualSize; i++)
    EXPECT_EQ_INT(2, columnSizes[i]);
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, array2DToStringSameCol(actual, actualSize, 2));

  free(columnSizes);
  array2DFree((void**)actual, actualSize);
  array2DFree((void**)words, wordsSize);
}

int main(void) {
  test("[[0,1],[1,0]]", "[bat,tab,cat]");
  test("[[0,1],[1,0],[2,4],[3,2]]", "[abcd,dcba,lls,s,sssll]");
  test("[[0,3],[2,3],[3,0],[3,2]]", "[a,abc,aba,]");

  return testOutput();
}
