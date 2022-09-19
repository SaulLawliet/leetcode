/*
 * Copyright (C) 2022, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 一看这是一个动态规划的问题, 分析后发现需要画一个二叉树的表格?
 * 头一次遇到这样的问题, 兴奋极了, 一顿操作下来
 * 又是 Memory Limit Exceeded, 又是 Time Limit Exceeded 的
 *
 * 下个文件再从头开始...
 */

#include <stdint.h>
#include "c/data-structures/array.h"
#include "c/test.h"

struct Cell {
  int v;  // value
  int p;  // [p, q]
  int q;
};

int maximumScore(int *nums, int numsSize, int *multipliers, int multipliersSize) {
  // 构建二叉树型表格
  struct Cell **table = malloc(sizeof(struct Cell *) * multipliersSize);
  for (int i = 0; i < multipliersSize; i++) {
    table[i] = malloc(sizeof(struct Cell) * (2 << i));
  }

  for (int i = 0; i < multipliersSize; i++) {
    for (int j = 0; j < 1 << i; j++) {
      struct Cell cell = i == 0 ? (struct Cell){0, 0, numsSize - 1} : table[i - 1][j];
      table[i][2 * j] = (struct Cell){cell.v + nums[cell.p] * multipliers[i], cell.p + 1, cell.q};
      table[i][2 * j + 1] = (struct Cell){cell.v + nums[cell.q] * multipliers[i], cell.p, cell.q - 1};
    }
  }

  int max = INT32_MIN;
  for (int i = 0; i < 1 << multipliersSize; i++) {
    if (table[multipliersSize - 1][i].v > max) {
      max = table[multipliersSize - 1][i].v;
    }
  }

  for (int i = 0; i < multipliersSize; i++) {
    free(table[i]);
  }
  free(table);

  return max;
}

void test(int expect, const char *nums, const char *multipliers) {
  arrayEntry *e1 = arrayParse1D(nums, ARRAY_INT);
  arrayEntry *e2 = arrayParse1D(multipliers, ARRAY_INT);

  EXPECT_EQ_INT(expect, maximumScore(arrayValue(e1), arraySize(e1), arrayValue(e2), arraySize(e2)));

  arrayFree(e2);
  arrayFree(e1);
}

int main(void) {
  test(14, "[1,2,3]", "[3,2,1]");
  test(102, "[-5,-3,-3,-2,7,1]", "[-10,-5,3,4,6]");

  return testOutput();
}
