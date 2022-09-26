/*
 * Copyright (C) 2022, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 先计算所有的‘==’, 分好组
 * 再计算所有的‘!=’, 如有同组的, 则 false
 *
 * 分组: 因为只要26个字母, 所以最多26个组, 然后对于每个等式, 把他们以递归的方式找到根部, 然后串起来
 */

#include <stdbool.h>
#include <stdint.h>
#include "c/data-structures/array.h"
#include "c/test.h"

int find(int8_t data[], int x) {
  if (data[x] == x) return x;
  return find(data, data[x]);
}

bool equationsPossible(char **equations, int equationsSize) {
  int8_t data[26];
  for (int i = 0; i < 26; i++) data[i] = i;

  for (int i = 0; i < equationsSize; i++) {
    if (equations[i][1] == '=') {
      data[find(data, equations[i][0] - 'a')] = find(data, equations[i][3] - 'a');
    }
  }

  for (int i = 0; i < equationsSize; i++) {
    if (equations[i][1] != '=') {
      if (find(data, data[equations[i][0] - 'a']) == find(data, data[equations[i][3] - 'a'])) {
        return false;
      }
    }
  }

  return true;
}

void test(bool expect, const char *equations) {
  arrayEntry *e = arrayParse1D(equations, ARRAY_STRING);
  EXPECT_EQ_INT(expect, equationsPossible(arrayValue(e), arraySize(e)));
  arrayFree(e);
}

int main(void) {
  test(false, "[a==b,b!=a]");
  test(true, "[a==b,b==a]");

  test(false, "[f==a,a==b,f!=e,a==c,b==e,c==f]");

  return testOutput();
}
