/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.

 * z 不能大于 MAX(x, y), 因为 z 一定要装在一个壶里.
 * 求出x和y的最大公约数, 然后看能不能被z整除, 就是该问题的解.
 */

#include <stdbool.h>
#include "../test.h"

int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a%b);
}

bool canMeasureWater(int x, int y, int z) {
  if (z > x && z > y) return false;
  return z % gcd(x, y) == 0;
}

void test(bool expect, int x, int y, int z) {
  EXPECT_EQ_INT(expect, canMeasureWater(x, y, z));
}

/*
  Input: x = 3, y = 5, z = 4
  Output: True

  Input: x = 2, y = 6, z = 5
  Output: False
 */
int main(void) {
  test(true, 3, 5, 4);
  test(false, 2, 6, 5);

  return testOutput();
}
