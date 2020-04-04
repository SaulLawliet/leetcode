/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 从头开始遍历, 遇到1前进两步, 遇到0前进一步.
 */

#include <stdbool.h>
#include "c/data-structures/array.h"
#include "c/test.h"

bool isOneBitCharacter(int *bits, int bitsSize) {
  int i = 0;
  while (i < bitsSize - 1) {
    i += bits[i] ? 2 : 1;
  }
  return i != bitsSize;
}

void test(bool expect, char *s) {
  arrayEntry *e = arrayParse1D(s, ARRAY_INT);

  EXPECT_EQ_INT(expect, isOneBitCharacter(arrayValue(e), arraySize(e)));

  arrayFree(e);
}

int main(void) {
  test(true, "[1, 0, 0]");
  test(false, "[1, 1, 1, 0]");

  return testOutput();
}
