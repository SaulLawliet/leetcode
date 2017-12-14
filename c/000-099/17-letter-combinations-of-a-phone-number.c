/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 使用循环列表来避免分配临时变量
 */

#include <string.h>  /* strlen() */
#include "../test.h"
#include "../data-structures/array.h"

/* start with '2' */
char *buttons[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tvu", "wxyz"};
int buttonLens[] = {3, 3, 3, 3, 3, 4, 3, 4};

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **letterCombinations(char *digits, int* returnSize) {
  int len = strlen(digits);
  if (len == 0) {
    *returnSize = 0;
    return NULL;
  }

  /* 计算 returnSize, 同时计算 startIndex, 这样结果比较美观 */
  *returnSize = 1;
  int startIndex = 0;
  for (int i = 0; i < len; i++) {
    int l = buttonLens[digits[i] - '2'];
    *returnSize *= l;
    startIndex += *returnSize;
  }
  if (startIndex == *returnSize) startIndex = 0;
  else startIndex = *returnSize - startIndex % *returnSize;

  char **rt = malloc(sizeof(char*) * *returnSize);
  for (int i = 0; i < *returnSize; i++)
    memset(rt[i] = malloc(sizeof(char) * (len + 1)), '\0', len + 1);


  int top = startIndex, oldTop = startIndex;
  for (int i = 0; i < len; i++) {
    int index = digits[i] - '2';
    char *b = buttons[index];
    if (i == 0) {
      while(*b) rt[top++][0] = *b++;
      continue;
    }
    int end = top;
    for (int j = oldTop; j != end; j++) {
      for (int k = 0; k < buttonLens[index]; k++) {
        int new = top % *returnSize;
        int prefix = j % *returnSize;
        if (new != prefix) strcpy(rt[new], rt[prefix]);
        rt[new][i] = b[k];
        top++;
      }
    }
    oldTop = end;
  }
  return rt;
}

void test(const char* expect, char* digits) {
  int actualSize;
  char** actual = letterCombinations(digits, &actualSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString1D(actual, actualSize, ARRAY_STRING));
}

int main(void) {
  test("[a,b,c]", "2");
  test("[ad,ae,af,bd,be,bf,cd,ce,cf]", "23");
  test("[adg,adh,adi,aeg,aeh,aei,afg,afh,afi,bdg,bdh,bdi,beg,beh,bei,bfg,bfh,bfi,cdg,cdh,cdi,ceg,ceh,cei,cfg,cfh,cfi]", "234");

  return testOutput();
}
