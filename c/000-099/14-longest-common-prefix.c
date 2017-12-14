/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 排除特殊情况后, 竖向对比, 以第一个为基准
 */

#include <stdlib.h>  /* malloc() */
#include <string.h>  /* strlen(), strncpy() */
#include "../test.h"
#include "../data-structures/array.h"

char *longestCommonPrefix(char **strs, int strsSize) {
  int i = 0;

  if (strsSize > 0) {
    int j, len = strlen(strs[0]);  /* 取第一个的长度为基准 */
    for (; i < len; i++) {
      for (j = 1; j < strsSize; j++) {
        if (strs[0][i] != strs[j][i]) {
          goto END;
        }
      }
    }
  }
END: {}
  char *rt = malloc(sizeof(char) * (i + 1));
  if (i > 0) strncpy(rt, strs[0], i);
  rt[i] = '\0';
  return rt;
}

void test(const char* expect, const char* str) {
  arrayEntry *e = arrayParse(str, ARRAY_STRING);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, longestCommonPrefix(arrayValue(e), arraySize(e)));

  arrayFree(e);
}

int main(void) {
  test("", "[]");

  test("a", "[a]");
  test("a", "[a, ac]");

  return testOutput();
}
