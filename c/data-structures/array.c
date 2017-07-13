/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include <stdlib.h>  /* malloc() */
#include <stdio.h>   /* sprintf() */
#include <assert.h>  /* assert() */
#include <string.h>  /* strtol(), strstr(), strncpy() */
#include <ctype.h>   /* isdigit() */
#include "array.h"
#include "../tools/stack.h"

int* arrayNewByStr(const char* str, size_t* size) {
  /* 依次从字符串中解析出整数 */
  context c = stackMake();

  int v;
  char *end;
  while (*str != '\0' && *str != ']') {
    if (isdigit(*str) || (*str == '-' && isdigit(*(str+1)))) {
      v = strtol(str, &end, 10);
      PUTI(&c, &v);
      str = end;
    } else {
      str++;
    }
  }

  *size = c.top / sizeof(int);
  return (int*)c.stack;
}

char* arrayToString(const int* array, size_t size) {
  if (size > 0) assert(array != NULL);
  context c = stackMake();

  int len;
  PUTC(&c, '[');
  for (size_t i = 0; i != size; ++i) {
    if (i > 0) PUTS(&c, ", ", 2);
    /* INT32_MIN = -2147483648, len = 11 */
    len = sprintf(stackPush(&c, 11), "%d", array[i]);
    c.top -= 11 - len;
  }
  PUTC(&c, ']');
  PUTC(&c, '\0');
  return c.stack;
}

int* arrayCopy(const int* array, size_t size) {
  if (array == NULL || size == 0) return NULL;
  return memcpy(malloc(sizeof(int) * size), array, sizeof(int) * size);
}

void array2DFree(void** array, size_t row) {
  for (size_t i = 0; i != row; ++i) free(array[i]);
  free(array);
}

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
int** array2DNewByStr(const char* str, size_t* row, size_t* col) {
  /* 以 ']' 为界, 分割成二维数组, col取最小的一个 */
  context c = stackMake();

  int* p;
  char* pos;
  size_t size, rtCol = 0;  /* max */
  while (*str != '\0') {
    p = arrayNewByStr(str, &size);
    if (size > 0) {  /* 忽略空的 */
      PUTIP(&c, &p);
      if (rtCol == 0) rtCol = size;
      else rtCol = MIN(rtCol, size);
    }

    pos = strstr(str, "]");
    if (pos == NULL) break;
    str += pos-str+1;
    while (*str == ']') str++;  /* 忽略连续的 ']' */
  }

  *row = c.top / sizeof(int*);
  *col = rtCol;
  return (int**)c.stack;
}

char* array2DToString(int** arrays, size_t row, size_t col) {
  if (row > 0) assert(arrays != NULL);
  context c = stackMake();

  PUTC(&c, '[');
  char *buffer;
  for (size_t i = 0; i != row; ++i) {
    if (i > 0) PUTS(&c, ", ", 2);
    buffer = arrayToString(arrays[i], col);
    PUTS(&c, buffer, strlen(buffer));
    free(buffer);
  }
  PUTC(&c, ']');
  PUTC(&c, '\0');
  return c.stack;
}

/* TODO: 写的比较恶心, 待优化 */
char** sarrayNewByStr(const char* str, size_t* size) {
  /* [Hello World, abcdefg, 0123456789] */
  while (*str == '[' || *str == ' ')  str++;

  context c = stackMake();

  int len;
  const char* tmp;
  char* p;
  while (*str != '\0' && *str != ']') {  /* 遇到 ']' 终止 */
    while (*str == ',' || *str == ' ') str++;  /* 移除首部空格和用来分割的',' */

    len = 0;
    tmp = str;

    while (*str != ',' && *str != ']' && *str != '\0') {  /* 计算长度 */
      str++;
      len++;
    }
    while (len > 0 && *(str-1) == ' ') {  /* 移除尾部空格 */
      str--;
      len--;
    }

    strncpy((p = malloc(sizeof(char) * (len+1))), tmp, len);
    p[len] = '\0';
    PUTCP(&c, &p);
  }

  *size = c.top / sizeof(char*);
  return (char**)c.stack;
}

char* sarrayToString(char** strs, size_t size) {
  if (size > 0) assert(strs != NULL);
  context c = stackMake();

  PUTC(&c, '[');
  for (size_t i = 0; i != size; ++i) {
    if (i > 0) PUTS(&c, ", ", 2);
    PUTS(&c, strs[i], strlen(strs[i]));
  }
  PUTC(&c, ']');
  PUTC(&c, '\0');
  return c.stack;
}
