/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 维护一个数组, 放入曾经计算过的值, 如果重复, 则失败.
 */

#include <math.h>
#include <stdbool.h>
#include "c/test.h"

struct Data {
  int arr[64];
  int size;
};

void add(struct Data *data, int value) {
  data->arr[data->size++] = value;
}

bool contains(struct Data *data, int value) {
  for (int i = 0; i < data->size; i++) {
    if (data->arr[i] == value) {
      return true;
    }
  }
  return false;
}

bool isHappy(int n) {
  struct Data data = {{}, 0};

  while (n != 1) {
    int sum = 0;
    while (n) {
      sum += pow(n % 10, 2);
      n /= 10;
    }
    if (contains(&data, sum)) return false;
    add(&data, n = sum);
  }
  return true;
}

void test(bool expect, int n) {
  EXPECT_EQ_INT(expect, isHappy(n));
}

int main(void) {
  test(false, 2);
  test(true, 19);

  return testOutput();
}
