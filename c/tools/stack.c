/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include "c/tools/stack.h"
#include <assert.h> /* assert() */
#include <stdlib.h> /* realloc() */

context stackMake(void) {
  context c;
  c.stack = NULL;
  c.size = c.top = 0;
  return c;
}

void *stackPush(context *c, size_t size) {
  void *ret;
  assert(size > 0);
  if (c->top + size >= c->size) {
    if (c->size == 0) c->size = STACK_INIT_SIZE;
    while (c->top + size >= c->size) {
      c->size += c->size >> 1; /* c->size * 1.5 */
    }
    c->stack = (char *)realloc(c->stack, c->size);
  }
  ret = c->stack + c->top;
  c->top += size;
  return ret;
}
