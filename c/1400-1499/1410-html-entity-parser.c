/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 字符串的批量替换问题.
 * 性能不是最优, 但代码还是很简单的.
 * 定义一个全局变量的替换字符的数组, 遍历即可.
 */

#include <stdlib.h> /* malloc() */
#include <string.h> /* strlen(), strncmp() */
#include "c/test.h"

struct character {
  char symbol;
  char *entry;
  int entryLen;
};

int N = 6;
struct character characters[] = {
    {'"', "&quot;", 6},
    {'\'', "&apos;", 6},
    {'&', "&amp;", 5},
    {'>', "&gt;", 4},
    {'<', "&lt;", 4},
    {'/', "&frasl;", 7}};

char *entityParser(char *text) {
  int i, len = strlen(text);
  char *rtn = malloc(sizeof(char) * (len + 1));
  char *p1 = text, *p2 = rtn;

  while (*p1 != '\0') {
    if (*p1 == '&') {
      for (i = 0; i < N; i++) {
        struct character c = characters[i];
        if (strncmp(c.entry, p1, c.entryLen) == 0) {
          p1 += c.entryLen;
          *p2++ = c.symbol;
          break;
        }
      }
      if (i < N) continue;
    }
    *p2++ = *p1++;
  }
  *p2 = '\0';
  return rtn;
}

void test(const char *expect, char *text) {
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, entityParser(text));
}

int main(void) {
  test("& is an HTML entity but &ambassador; is not.", "&amp; is an HTML entity but &ambassador; is not.");
  test("and I quote: \"...\"", "and I quote: &quot;...&quot;");
  test("Stay home! Practice on Leetcode :)", "Stay home! Practice on Leetcode :)");
  test("x > y && x < y is always false", "x &gt; y &amp;&amp; x &lt; y is always false");
  test("leetcode.com/problemset/all", "leetcode.com&frasl;problemset&frasl;all");
  return testOutput();
}
