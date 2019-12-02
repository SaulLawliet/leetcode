/*
 * Copyright (C) 2019, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 朴素解法:
 * 初始化每一行的时候用空格填满,
 * 依次放入"单词", 如果超出限制, 就开始调整本行的位置
 * 具体操作流程是: 算出移位的个数, 从后向前不断的交换字符的位置, 直到处理完毕
 */

#include <stdlib.h> /* malloc() */
#include <string.h> /* memset(), strlen(), strncpy() */
#include "c/data-structures/array.h"
#include "c/test.h"

int N = 100;
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **fullJustify(char **words, int wordsSize, int maxWidth, int *returnSize) {
  char **rtn = malloc(sizeof(char *) * N);

  int pos = 0, count = 0;
  *returnSize = 0;
  rtn[*returnSize] = malloc(maxWidth + 1);
  memset(rtn[*returnSize], ' ', maxWidth);
  rtn[*returnSize][maxWidth] = '\0';

  for (int i = 0; i < wordsSize; i++) {
    int wordsLength = strlen(words[i]);
    if (pos + wordsLength >= maxWidth && pos > 0) { /* 需要换行 */
      /* 先对齐本行的数据 */
      int space = maxWidth - pos; /* 一共需要填入的空格数 */
      int n = space;
      int k = --count; /* 还有几个空需要插入 */
      while (pos > 0 && k > 0) {
        pos--;
        char c = rtn[*returnSize][pos];

        if (c == ' ') {
          n -= space / count + (space % count > --k ? 1 : 0);
        } else {
          /** 交换位置 */
          rtn[*returnSize][pos] = ' ';
          rtn[*returnSize][pos + n] = c;
        }
      }

      /* 初始化新一行 */
      pos = 0, count = 0;
      (*returnSize)++;
      rtn[*returnSize] = malloc(maxWidth + 1);
      memset(rtn[*returnSize], ' ', maxWidth);
      rtn[*returnSize][maxWidth] = '\0';
    }

    if (count > 0) pos++;
    strncpy(rtn[*returnSize] + pos, words[i], wordsLength);
    pos += wordsLength;

    count++;
  }
  (*returnSize)++;
  return rtn;
}

void test(const char *expect, char *s, int maxWidth) {
  arrayEntry *e = arrayParse1D(s, ARRAY_STRING);
  int returnSize;
  char **rtn = fullJustify(arrayValue(e), arraySize(e), maxWidth, &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString1D(rtn, returnSize, ARRAY_STRING));

  arrayFree(e);
}

int main(void) {
  test("[This    is    an,example  of text,justification.  ]",
       "[This, is, an, example, of, text, justification.]",
       16);

  test("[What   must   be,acknowledgment  ,shall be        ]",
       "[What, must, be, acknowledgment, shall, be]",
       16);

  test("[Science  is  what we,understand      well,enough to explain to,a  computer.  Art is,everything  else  we,do                  ]",
       "[Science, is, what, we, understand, well, enough, to, explain, to, a, computer., Art, is, everything, else, we, do]",
       20);

  return testOutput();
}
