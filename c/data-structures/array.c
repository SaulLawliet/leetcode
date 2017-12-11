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

int* arrayNewByStr(const char* str, int* size) {
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

char* arrayToString(const int* array, int size) {
  // if (size > 0) assert(array != NULL);
  context c = stackMake();

  int len;
  PUTC(&c, '[');
  for (int i = 0; i < size; ++i) {
    if (i > 0) PUTC(&c, ',');
    /* INT32_MIN = -2147483648, len = 11 */
    len = sprintf(stackPush(&c, 11), "%d", array[i]);
    c.top -= 11 - len;
  }
  PUTC(&c, ']');
  PUTC(&c, '\0');
  return c.stack;
}

int* arrayCopy(const int* array, int size) {
  if (array == NULL || size == 0) return NULL;
  return memcpy(malloc(sizeof(int) * size), array, sizeof(int) * size);
}

void array2DFree(void** array, int row) {
  for (int i = 0; i < row; ++i) free(array[i]);
  free(array);
}

int** array2DNewByStr(const char* str, int* row, int** cols) {
  /* 以 ']' 为界, 分割成二维数组, col取最小的一个 */
  context c = stackMake();
  context c2 = stackMake();

  int* p;
  char* pos;
  int size;
  while (*str != '\0') {
    p = arrayNewByStr(str, &size);
    PUTIP(&c, &p);
    PUTI(&c2, &size);

    pos = strstr(str, "]");
    if (pos == NULL) break;
    str += pos-str+1;
    while (*str == ']') str++;  /* 忽略连续的 ']' */
  }

  *row = c.top / sizeof(int*);
  *cols = (int*)c2.stack;
  return (int**)c.stack;
}

char* array2DToString(int** arrays, int row, int* cols) {
  if (row > 0) assert(arrays != NULL);
  context c = stackMake();

  PUTC(&c, '[');
  char *buffer;
  for (int i = 0; i < row; ++i) {
    if (i > 0) PUTC(&c, ',');
    buffer = arrayToString(arrays[i], cols[i]);
    PUTS(&c, buffer, strlen(buffer));
    free(buffer);
  }
  PUTC(&c, ']');
  PUTC(&c, '\0');
  return c.stack;
}

int** array2DNewByStrSameCol(const char* str, int* row, int* col) {
  int* cols;
  int** rtn = array2DNewByStr(str, row, &cols);
  *col = row > 0 ? cols[0] : 0;
  free(cols);
  return rtn;
}

char* array2DToStringSameCol(int** arrays, int row, int col) {
  assert(row > 0);
  int* cols = malloc(sizeof(int) * row);
  for (int i = 0; i < row; ++i) cols[i] = col;
  char* rtn = array2DToString(arrays, row, cols);
  free(cols);
  return rtn;
}

/* TODO: 写的比较恶心, 待优化 */
char** sarrayNewByStr(const char* str, int* size) {
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

char* sarrayToString(char** strs, int size) {
  if (size > 0) assert(strs != NULL);
  context c = stackMake();

  PUTC(&c, '[');
  for (int i = 0; i < size; ++i) {
    if (i > 0) PUTC(&c, ',');
    PUTS(&c, strs[i], strlen(strs[i]));
  }
  PUTC(&c, ']');
  PUTC(&c, '\0');
  return c.stack;
}

double* darrayNewByStr(const char* str, int* size) {
  context c = stackMake();

  double v;
  char *end;
  while (*str != '\0' && *str != ']') {
    if (isdigit(*str) || (*str == '-' && isdigit(*(str+1)))) {
      v = strtod(str, &end);
      PUTD(&c, &v);
      str = end;
    } else {
      str++;
    }
  }

  *size = c.top / sizeof(double);
  return (double*)c.stack;
}

char* darrayToString(const double* array, int size, int precision) {
  context c = stackMake();

  int len;
  PUTC(&c, '[');
  for (int i = 0; i < size; ++i) {
    if (i > 0) PUTC(&c, ',');
    /* 假设最长是100 */
    len = sprintf(stackPush(&c, 100), "%.*f", precision, array[i]);
    c.top -= 100 - len;
  }
  PUTC(&c, ']');
  PUTC(&c, '\0');
  return c.stack;
}
