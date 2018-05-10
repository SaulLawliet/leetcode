/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#ifndef TOOLS_STACK_H_
#define TOOLS_STACK_H_

#include <string.h> /* memcpy() */

#ifndef STACK_INIT_SIZE
#define STACK_INIT_SIZE 64
#endif

#define PUT(c, v)        do { *(context *)stackPush(c, sizeof(context)) = (v);} while (0)
#define PUTC(c, v)       do { *(char *)stackPush(c, sizeof(char)) = (v); } while (0)
#define PUTI(c, v)       do { *(int *)stackPush(c, sizeof(int)) = (v); } while (0)
#define PUTD(c, v)       do { *(double *)stackPush(c, sizeof(double)) = (v); } while (0)
#define PUTD(c, v)       do { *(double *)stackPush(c, sizeof(double)) = (v); } while (0)
#define PUTCP(c, v)      do { *(char **)stackPush(c, sizeof(char*)) = (v); } while (0)

#define PUTS(c, s, len)  do { if (len > 0) memcpy(stackPush(c, len), s, len); } while (0)

typedef struct {
  char *stack;
  size_t size, top;
} context;

context stackMake(void);
void *stackPush(context *c, size_t size);

#endif /* TOOLS_STACK_H_ */
