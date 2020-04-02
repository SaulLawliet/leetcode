/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 用二维数组标记图的联通关系, dfs 更新每个点的数值, 最后统计最大值.
 */

#include <string.h>
#include "c/data-structures/array.h"
#include "c/test.h"

void dfs(int *nodes, int *data, int N, int k) {
  for (int i = 0; i < N; i++) {
    int time = nodes[k * N + i];
    if (time >= 0) {
      time += data[k];
      if (data[i] == -1 || data[i] > time) {
        data[i] = time;
        dfs(nodes, data, N, i);
      }
    }
  }
}

int networkDelayTime(int **times, int timesSize, int *timesColSize, int N, int K) {
  int nodes[N][N];
  int data[N];
  for (int i = 0; i < N; i++) {
    data[i] = -1;
    for (int j = 0; j < N; j++)
      nodes[i][j] = -1;
  }

  for (int i = 0; i < timesSize; i++) {
    nodes[times[i][0] - 1][times[i][1] - 1] = times[i][2];
  }

  data[K - 1] = 0;
  dfs(*nodes, data, N, K - 1);

  int time = 0;
  for (int i = 0; i < N; i++) {
    if (data[i] < 0) return -1;
    if (data[i] > time) time = data[i];
  }
  return time;
}

void test(int expect, char *s, int N, int K) {
  arrayEntry *e = arrayParse2D(s, ARRAY_INT);

  EXPECT_EQ_INT(expect, networkDelayTime(arrayValue(e), arrayRow(e), arrayCols(e), N, K));

  arrayFree(e);
}

int main(void) {
  test(2, "[[2,1,1],[2,3,1],[3,4,1]]", 4, 2);

  test(3, "[[1,2,1],[2,1,3]]", 2, 2);

  return testOutput();
}
