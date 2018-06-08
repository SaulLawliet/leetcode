/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 前缀树
 * 1. 有 "a, aa, aaa, aaaa" 时, 只匹配 "a"
 * 2. 当我提交的时候, 提示内存超出, 所以 trieNode 中的 children 要在使用中才申请空间
 * 3. 看了结果之后, 原来暴力破解也能AC
 */

#include <stdbool.h>
#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* strlen(), memcpy() */
#include "c/data-structures/array.h"
#include "c/test.h"

#define SIZE 26

typedef struct trieNode trieNode;
struct trieNode {
  bool word;
  trieNode **children;
};

trieNode *makeTrieNode() {
  trieNode *node = malloc(sizeof(trieNode));
  node->word = false;
  node->children = NULL;
  return node;
}

void freeTrieNode(trieNode *node) {
  if (node == NULL) return;
  if (node->children != NULL) {
    for (int i = 0; i < SIZE; ++i)
      freeTrieNode(node->children[i]);
    free(node->children);
  }
  free(node);
}

trieNode *buildTrie(char **dict, int dictSize) {
  trieNode *root = makeTrieNode();
  trieNode *cur;
  for (int i = 0; i < dictSize; ++i) {
    cur = root;
    char *p = dict[i];
    while (*p) {
      if (cur->word) break;

      if (cur->children == NULL) {
        cur->children = malloc(sizeof(trieNode *) * SIZE);
        for (int i = 0; i < SIZE; ++i)
          cur->children[i] = NULL;
      }

      if (cur->children[*p - 'a'] == NULL)
        cur->children[*p - 'a'] = makeTrieNode();
      cur = cur->children[*p - 'a'];
      p++;
    }
    cur->word = true;
  }
  return root;
}

int findInTrie(trieNode *node, char *word) {
  int rtn = 0;
  while (*word != '\0' && *word != ' ') {
    if (node == NULL) break;
    if (node->word) return rtn;
    if (node->children == NULL) break;
    rtn++;
    node = node->children[*word++ - 'a'];
  }
  return 0;
}

char *replaceWords(char **dict, int dictSize, char *sentence) {
  trieNode *node = buildTrie(dict, dictSize);
  char *p1 = sentence, *p2 = sentence;
  while (*p2) {
    int count = findInTrie(node, p2);
    if (count == 0) {
      while (*p2 != ' ' && *p2 != '\0') *p1++ = *p2++;
    } else {
      while (count--) *p1++ = *p2++;
      while (*p2 != ' ' && *p2 != '\0') p2++;
    }
    if (*p2 != '\0') {
      p2++;
      *p1++ = ' ';
    }
  }
  if (p1 != p2) *p1 = '\0';
  freeTrieNode(node);
  return sentence;
}

void test(const char *expect, const char *dictStr, const char *str) {
  int len = strlen(str);
  char *sentence = malloc(sizeof(char) * (len + 1));
  memcpy(sentence, str, len);
  sentence[len] = '\0';
  arrayEntry *e = arrayParse1D(dictStr, ARRAY_STRING);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, replaceWords(arrayValue(e), arraySize(e), sentence));

  arrayFree(e);
}

int main(void) {
  test("the cat was rat by the bat",
       "[cat, bat, rat]",
       "the cattle was rattled by the battery");

  test("the cattle was rattled by the battery",
       "[]",
       "the cattle was rattled by the battery");

  test("a a a a a a a a bbb baba a",
       "[a, aa, aaa, aaaa]",
       "a aa a aaaa aaa aaa aaa aaaaaa bbb baba ababa");

  testOutput();
}
