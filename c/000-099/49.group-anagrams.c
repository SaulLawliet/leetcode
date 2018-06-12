/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 利用素数的特性和乘法分配律, 来计算 hash, 同组的 hash 一定相等
 * 如果将每组的 hash 存到 HashMap 中, 将会提升查找性能, 但为了处理方便, 暂时放在数组中(代码中的hashTable)
 */

#include <stdbool.h>
#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* strlen(), memcpy() */
#include "c/data-structures/array.h"
#include "c/data-structures/linked-list.h"
#include "c/test.h"

int PRIME_NUMBERS[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
int hashCode(char *str) {
  int hash = 1;
  while (*str) hash *= PRIME_NUMBERS[*str++ - 'a'];
  return hash;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char ***groupAnagrams(char **strs, int strsSize, int **columnSizes, int *returnSize) {
  *returnSize = 0;
  *columnSizes = malloc(sizeof(int) * strsSize);

  char ***rtn = malloc(sizeof(char **) * strsSize);
  int *hashTable = malloc(sizeof(int) * strsSize);

  for (int i = 0; i < strsSize; ++i) {
    int hash = hashCode(strs[i]), row = -1;

    for (int j = 0; j < *returnSize; ++j)
      if (hashTable[j] == hash) {
        row = j;
        break;
      }

    if (row == -1) {
      /* first */
      row = (*returnSize)++;
      rtn[row] = malloc(sizeof(char *) * strsSize);
      (*columnSizes)[row] = 0;
      hashTable[row] = hash;
    }

    int len = strlen(strs[i]) + 1,
        col = (*columnSizes)[row]++;
    memcpy(rtn[row][col] = malloc(len), strs[i], len);
  }

  free(hashTable);
  return rtn;
}

void test(const char *expect, const char *s) {
  arrayEntry *e = arrayParse1D(s, ARRAY_STRING);
  int returnSize;
  int *columnSizes;
  char ***rtn = groupAnagrams(arrayValue(e), arraySize(e), &columnSizes, &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString2D(rtn, returnSize, columnSizes, ARRAY_STRING));

  arrayFree(e);
}

int main(void) {
  test("[[eat,tea,ate],[tan,nat],[bat]]",
       "[eat,tea,tan,ate,nat,bat]");

  testOutput();
}
