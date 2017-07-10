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
  /* "[]", "[1, 2, 3]" */
  assert(str[0] == '[');
  assert(strstr(str, "]") != NULL);
  str++;

  context c = stackMake();

  int v;
  char *end;
  while (*str != ']') {
    v = strtol(str, &end, 10);
    PUTI(&c, &v);
    str = end;
    while (*str != ']') {
      if (isdigit(*str) || (*str == '-' && isdigit(*(str+1)))) {
        break;
      }
      str++;
    }
  }

  *size = c.top / sizeof(int);
  return (int*)c.stack;
}

char* arrayToString(const int* array, size_t size) {
  context c = stackMake();

  if (array == NULL || size == 0) {
    PUTS(&c, "[]", 3);
    return c.stack;
  }

  PUTC(&c, '[');
  int len;
  for (size_t i = 0; i != size; ++i) {
    /* INT32_MIN = -2147483648, len = 11
     * len(", ") = 2, total = 13 */
    len = sprintf(stackPush(&c, 13), "%d, ", array[i]);
    c.top -= 13 - len;
  }
  c.stack[c.top - 2] = ']';
  c.stack[c.top - 1] = '\0';
  return c.stack;
}

int* arrayCopy(const int* array, size_t size) {
  if (array == NULL || size == 0) return NULL;
  return memcpy(malloc(sizeof(int) * size), array, sizeof(int) * size);
}

int** array2DNewByStr(const char* str, size_t* row, size_t* col) {
  /* "[]", "[[1, 2], [3, 4]]" */
  assert(str[0] == '[');
  assert(strstr(str, "]") != NULL);
  str++;

  context c = stackMake();

  int len;
  int* p;
  char* pos = NULL;
  char* buffer = NULL;
  while (*str != '\0' && (pos = strstr(str, "]")) != NULL) {
    len = pos - str + 1;
    buffer = malloc(sizeof(char) * len);
    strncpy(buffer, str, len);

    p = arrayNewByStr(buffer, col);
    PUTIP(&c, &p);

    free(buffer);

    str += len;
    while (*str != '[' && *str != '\0') str++;
  }

  *row = c.top / sizeof(int*);
  return (int**)c.stack;
}

void array2DFree(int** array, size_t row) {
  for (size_t i = 0; i != row; ++i) free(array[i]);
  free(array);
}
