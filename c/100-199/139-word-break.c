/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * v1: 先想到的是dps, 提交后, 有个测试用例超时(全是a的那个), 代码就先不删掉(解题思路有问题)
 * v2: 标准的动态规划, 计算所有可能性
 * v3: 参考耗时最少的写法, 利用词典来匹配字符串, 同时增加一个辅助位置来优化编码, 取下标的时候可以不必"-1"
 */

#include <stdbool.h>
#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* strlen(), memset() */
#include "c/data-structures/array.h"
#include "c/test.h"

bool find(char *s, char **wordDict, int wordDictSize, int index, int target) {
  int p;
  for (int i = 0; i < wordDictSize; i++) {
    p = 0;
    while (wordDict[i][p] != '\0' && s[index + p] != '\0') {
      if (wordDict[i][p] != s[index + p]) break;
      p++;
    }

    if (wordDict[i][p] == '\0') {
      /* 此时说明完全匹配, 继续往下查找 */
      if (index + p == target || find(s, wordDict, wordDictSize, index + p, target)) {
        return true;
      }
    }
  }
  return false;
}

/** 深度优先, 超时 */
bool wordBreak_v1(char *s, char **wordDict, int wordDictSize) {
  return find(s, wordDict, wordDictSize, 0, strlen(s));
}

bool wordBreak_v2(char *s, char **wordDict, int wordDictSize) {
  int len = strlen(s);
  bool *dp = memset(malloc(len), 0, len);

  /* 缓存一下词典里面每个词的长度 */
  int *wordLen = malloc(sizeof(int) * wordDictSize);
  for (int i = 0; i < wordDictSize; i++) {
    wordLen[i] = strlen(wordDict[i]);
  }

  for (int i = 0; i < len; i++) {
    for (int j = 0; j <= i; j++) {
      if (j == 0 || dp[j - 1]) {
        int l = i - j + 1;
        for (int k = 0; k < wordDictSize; k++) {
          if (wordLen[k] == l && !strncmp(wordDict[k], s + j, l)) {
            dp[i] = true;
            break;
          }
        }
      }
    }
  }

  bool result = dp[len-1];

  free(wordLen);
  free(dp);

  return result;
}

bool wordBreak_v3(char *s, char **wordDict, int wordDictSize) {
  int len = strlen(s);
  bool *dp = memset(malloc(len+1), 0, len+1);
  dp[0] = true;

  /* 缓存一下词典里面每个词的长度 */
  int *wordLen = malloc(sizeof(int) * wordDictSize);
  for (int i = 0; i < wordDictSize; i++) {
    wordLen[i] = strlen(wordDict[i]);
  }

  for (int i = 0; i < len; i++) {
    if (dp[i]) {
      for (int k = 0; k < wordDictSize; k++) {
        int l = wordLen[k];
        if (i + l <= len && !strncmp(wordDict[k], s+i, l)) {
          dp[i+l] = true;
        }
      }
    }
  }
  bool result = dp[len];

  free(wordLen);
  free(dp);

  return result;
}

void test(bool expect, char *s, const char *wordDict) {
  arrayEntry *e = arrayParse1D(wordDict, ARRAY_STRING);

  // v1: 测试用例4超时
  // EXPECT_EQ_INT(expect, wordBreak_v1(s, arrayValue(e), arraySize(e)));

  EXPECT_EQ_INT(expect, wordBreak_v2(s, arrayValue(e), arraySize(e)));
  EXPECT_EQ_INT(expect, wordBreak_v3(s, arrayValue(e), arraySize(e)));

  arrayFree(e);
}

int main(void) {
  test(true, "leetcode", "[leet, code]");
  test(true, "applepenapple", "[apple, pen]");
  test(false, "catsandog", "[cats, dog, sand, and, cat]");

  test(false, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab",
       "[a, aa, aaa, aaaa, aaaaa, aaaaaa, aaaaaaa, aaaaaaaa, aaaaaaaaa, aaaaaaaaaa]");

  return testOutput();
}
