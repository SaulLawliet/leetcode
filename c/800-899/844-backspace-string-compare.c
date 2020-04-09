/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 刚读题目的时候, 很容易就会想到, 此类问题用栈来解很容易.
 * 但题目的最后规定是 时间: O(N), 空间: O(1).
 * 所以就不能使用栈, 因为栈的空间是O(N).
 *
 * 那么大概率就是用两个指针来解题.
 * 从前向后找时, 会发现需要依赖后面的'#', 但无法得知后面的'#'有几个.
 * 因此, 两个指针应该是从后向前移动.
 *
 * 时间: O(len(S) + len(T) + while(len(S)) + while(len(T)))
 *        => O(2 * (len(S) + len(T)))
 *        => O(4N)
 *        => O(N)
 */

#include <stdbool.h>
#include <string.h>
#include "c/test.h"

bool backspaceCompare(char *S, char *T) {
  int i1 = strlen(S) - 1, i2 = strlen(T) - 1;
  int c1 = 0, c2 = 0;
  while (i1 >= 0 || i2 >= 0) {
    while (i1 >= 0) {
      if (S[i1] == '#')
        ++c1, --i1;
      else if (c1 > 0)
        --c1, --i1;
      else
        break;
    }

    while (i2 >= 0) {
      if (T[i2] == '#')
        ++c2, --i2;
      else if (c2 > 0)
        --c2, --i2;
      else
        break;
    }

    if (i1 >= 0 && i2 >= 0 && S[i1] != T[i2]) {
      return false;
    }
    --i1, --i2;
  }
  return i1 == i2;
}

void test(bool expect, char *S, char *T) {
  EXPECT_EQ_INT(expect, backspaceCompare(S, T));
}

int main(void) {
  test(true, "ab#c", "ad#c");
  test(true, "ab##", "c#c#");
  test(true, "a##c", "#a#c");
  test(false, "a#c", "b");

  test(false, "bxj##tw", "bxj###tw");

  return testOutput();
}
