/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 蛮力解法
 */

#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* memset() */
#include "c/data-structures/array.h"
#include "c/test.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *distributeCandies(int candies, int num_people, int *returnSize) {
  int *rtn = malloc(sizeof(int) * num_people);
  memset(rtn, 0, sizeof(int) * num_people);

  int i = 0, tmp;
  while (candies > 0) {
    tmp = i+1 < candies ? i+1 : candies;
    rtn[i++%num_people] += tmp;
    candies -= tmp;
  }

  *returnSize = num_people;
  return rtn;
}

void test(const char *expect, int candies, int num_people) {
  int returnSize;
  int *rtn = distributeCandies(candies, num_people, &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString1D(rtn, returnSize, ARRAY_INT));
}

int main(void) {
  test("[1,2,3,1]", 7, 4);
  test("[5,2,3]", 10, 3);

  return testOutput();
}
