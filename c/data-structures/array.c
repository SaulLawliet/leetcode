/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include "data-structures/array.h"
#include <assert.h> /* assert() */
#include <stdbool.h>
#include <stdio.h>  /* snprintf() */
#include <stdlib.h> /* malloc(), strtol(), strtod() */
#include <string.h> /* strncpy() */
#include "tools/stack.h"

#define EXPECT(str, c)  do { assert(**str == (c)); (*str)++; } while (0)

struct arrayEntry {
  arrayType type;
  int size;
  void *v;
  int *cols;
  int precision; /* printf: float precision */
};

arrayEntry *arrayNew(arrayType type) {
  arrayEntry *e = malloc(sizeof(arrayEntry));
  e->type = type;
  e->v = NULL;
  e->size = 0;
  e->cols = NULL;
  e->precision = 0;
  return e;
}

static void parseWhitespace(const char **str) {
  const char *p = *str;
  while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') p++;
  *str = p;
}

static void parseChar(const char **str, context *c) {
  PUTC(c, **str);
  (*str)++;
}

static void parseInt(const char **str, context *c) {
  PUTI(c, strtol(*str, (char **)str, 10));
}

static void parseDouble(const char **str, context *c) {
  PUTD(c, strtod(*str, (char **)str));
}

static void parseString(const char **str, context *c) {
  const char *p = *str;
  int len = 0;
  while (*p != ',' && *p != ']' && *p != '\0') { p++; len++; }
  while (len > 0 && *(p - 1) == ' ') { p--; len--; }

  char *buf = malloc(sizeof(char) * (len + 1));
  strncpy(buf, *str, len);
  buf[len] = '\0';
  PUTCP(c, buf);

  *str = p;
}

static context parseArray(const char **str, arrayType type, int dimensional) {
  EXPECT(str, '[');
  parseWhitespace(str);

  context c = stackMake();
  if (**str != ']') {
    for (;;) {
      if (dimensional > 1) {
        PUT(&c, parseArray(str, type, dimensional - 1));
      } else {
        switch (type) {
          case ARRAY_CHAR: parseChar(str, &c); break;
          case ARRAY_INT: parseInt(str, &c); break;
          case ARRAY_DOUBLE: parseDouble(str, &c); break;
          case ARRAY_STRING: parseString(str, &c); break;
        }
      }
      parseWhitespace(str);

      if (**str == ',') {
        (*str)++;
        parseWhitespace(str);
      } else if (**str == ']') {
        (*str)++;
        break;
      } else {
        assert(false); /* miss ',' or ']' */
      }
    }
  }

  return c;
}

static int sizeOf(arrayType type) {
  switch (type) {
    case ARRAY_CHAR: return sizeof(char);
    case ARRAY_INT: return sizeof(int);
    case ARRAY_DOUBLE: return sizeof(double);
    case ARRAY_STRING: return sizeof(char *);
  }
  return 0;
}

arrayEntry *arrayParse(const char *str, arrayType type) {
  const char *p = str;
  parseWhitespace(&p);
  if (*p == '[') {
    p++;
    parseWhitespace(&p);
    if (*p == '[') {
      return arrayParse2D(str, type);
    }
  }
  return arrayParse1D(str, type);
}

arrayEntry *arrayParse1D(const char *str, arrayType type) {
  parseWhitespace(&str);
  context c = parseArray(&str, type, 1);
  arrayEntry *e = arrayNew(type);
  e->size = c.top / sizeOf(type);
  e->v = c.stack;
  return e;
}

arrayEntry *arrayParse2D(const char *str, arrayType type) {
  parseWhitespace(&str);
  context c = parseArray(&str, type, 2);

  arrayEntry *e = arrayNew(type);
  e->size = c.top / sizeof(context);
  e->cols = malloc(sizeof(int) * e->size);

  void **v = malloc(sizeof(void *) * e->size);
  for (int i = 0; i < e->size; ++i) {
    v[i] = ((context *)c.stack)[i].stack;
    e->cols[i] = ((context *)c.stack)[i].top / sizeOf(type);
  }
  e->v = v;

  free(c.stack);
  return e;
}

static void free2D(void **v, int size) {
  for (int i = 0; i < size; ++i) free(v[i]);
  free(v);
}

void arrayFree(arrayEntry *entry) {
  if (entry->cols == NULL) {
    if (entry->type == ARRAY_STRING)
      free2D((void **)entry->v, entry->size);
    else
      free(entry->v);
  } else {
    if (entry->type == ARRAY_STRING) {
      for (int i = 0; i < entry->size; ++i)
        free2D(((void **)entry->v)[i], entry->cols[i]);
      free(entry->v);
    } else {
      free2D((void **)entry->v, entry->size);
    }

    free(entry->cols);
  }
  free(entry);
}

arrayEntry *arrayFrom1D(void *v, int size, arrayType type) {
  arrayEntry *e = arrayNew(type);
  e->v = v;
  e->size = size;
  return e;
}

arrayEntry *arrayFrom2D(void *v, int row, int *cols, arrayType type) {
  arrayEntry *e = arrayNew(type);
  e->v = v;
  e->size = row;
  e->cols = cols;
  return e;
}

arrayEntry *arrayFrom2DSameCol(void *v, int row, int col, arrayType type) {
  int *cols = malloc(sizeof(int) * row);
  for (int i = 0; i < row; ++i) cols[i] = col;
  return arrayFrom2D(v, row, cols, type);
}

void toString(context *c, char *v, int size, arrayType type, int precision) {
  PUTC(c, '[');
  for (int i = 0; i < size; ++i) {
    if (i > 0) PUTC(c, ',');
    switch (type) {
      case ARRAY_CHAR:
        PUTC(c, v[i]);
        break;
      case ARRAY_INT:
        c->top -= 32 - snprintf(stackPush(c, 32), 32, "%d", ((int *)v)[i]);
        break;
      case ARRAY_DOUBLE:
        assert(precision != 0);
        c->top -= 32 - snprintf(stackPush(c, 32), 32, "%.*f", precision, ((double *)v)[i]);
        break;
      case ARRAY_STRING:
        PUTS(c, ((char **)v)[i], strlen(((char **)v)[i]));
        break;
    }
  }
  PUTC(c, ']');
}

char *arrayToString(arrayEntry *entry) {
  context c = stackMake();
  if (entry->cols == NULL) {
    toString(&c, entry->v, entry->size, entry->type, entry->precision);
  } else {
    PUTC(&c, '[');
    for (int i = 0; i < entry->size; ++i) {
      if (i > 0) PUTC(&c, ',');
      toString(&c, ((void **)entry->v)[i], entry->cols[i], entry->type, entry->precision);
    }
    PUTC(&c, ']');
  }

  PUTC(&c, '\0');
  return c.stack;
}

char *arrayToString1D(void *v, int size, arrayType type) {
  arrayEntry *e = arrayFrom1D(v, size, type);
  char *rt = arrayToString(e);
  arrayFree(e);
  return rt;
}

char *arrayToString2D(void *v, int row, int *cols, arrayType type) {
  arrayEntry *e = arrayFrom2D(v, row, cols, type);
  char *rt = arrayToString(e);
  arrayFree(e);
  return rt;
}

char *arrayToString2DSameCol(void *v, int row, int col, arrayType type) {
  arrayEntry *e = arrayFrom2DSameCol(v, row, col, type);
  char *rt = arrayToString(e);
  arrayFree(e);
  return rt;
}

void *arrayValue(arrayEntry *entry) { return entry->v; }
int arraySize(arrayEntry *entry) { return entry->size; }
void arraySetSize(arrayEntry *entry, int size) { entry->size = size; }

void arraySetPrecision(arrayEntry *entry, int precision) { entry->precision = precision; }

int arrayRow(arrayEntry *entry) { return entry->size; }
int *arrayCols(arrayEntry *entry) { return entry->cols; }
int arrayCol(arrayEntry *entry) {
  if (entry->cols != NULL && entry->size > 0)
    return entry->cols[0];
  else
    return 0;
}
