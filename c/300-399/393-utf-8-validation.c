/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include <stdbool.h>
#include "c/data-structures/array.h"
#include "c/test.h"

bool validUtf8(int *data, int dataSize) {
  int count = 0;
  for (int i = 0; i < dataSize; ++i) {
    if (count == 0) {
      if (data[i] >> 7 == 0x0)       count = 0;
      else if (data[i] >> 5 == 0x6)  count = 1;
      else if (data[i] >> 4 == 0xE)  count = 2;
      else if (data[i] >> 3 == 0x1E) count = 3;
      else return false;
    } else {
      if (data[i] >> 6 != 0x2) return false;
      count--;
    }
  }
  return count == 0;
}

void test(bool expect, const char *str) {
  arrayEntry *e = arrayParse(str, ARRAY_INT);

  EXPECT_EQ_INT(expect, validUtf8(arrayValue(e), arraySize(e)));

  arrayFree(e);
}

/*
  Char. number range  |        UTF-8 octet sequence
     (hexadecimal)    |              (binary)
  --------------------+---------------------------------------------
  0000 0000-0000 007F | 0xxxxxxx
  0000 0080-0000 07FF | 110xxxxx 10xxxxxx
  0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
  0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 */
int main(void) {
  test(true, "[197, 130, 1]");
  test(false, "[235, 140, 4]");

  return testOutput();
}
