/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#ifndef __TEST_H
#define __TEST_H

#include <stdio.h>   /* printf(), fprintf() */
#include <string.h>  /* strcmp() */
#include <stdlib.h>  /* free() */

static int test_main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format)                \
  do {                                                                  \
    test_count++;                                                       \
    if (equality) {                                                     \
      test_pass++;                                                      \
    } else {                                                            \
      fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", \
              __FILE__, __LINE__, expect, actual);                      \
      test_main_ret = 1;                                                \
    }                                                                   \
  } while (0)

#define EXPECT_EQ_INT(expect, actual)           \
  do {                                          \
    int n1 = expect, n2 = actual;               \
    EXPECT_EQ_BASE(n1 == n2, n1, n2, "%d");     \
  } while (0)

#define EXPECT_EQ_DOUBLE(expect, actual)        \
  do {                                          \
    double n1 = expect, n2 = actual;            \
    EXPECT_EQ_BASE(n1 == n2, n1, n2, "%.17g");  \
  } while (0)

#define EXPECT_EQ_STRING(expect, actual)                \
  do {                                                  \
    char *s1 = expect, *s2 = actual;                    \
    EXPECT_EQ_BASE(strcmp(s1, s2) == 0, s1, s2, "%s");  \
  } while (0)

#define EXPECT_EQ_STRING_AND_FREE(expect, actual)       \
  do {                                                  \
    char *s1 = expect, *s2 = actual;                    \
    EXPECT_EQ_BASE(strcmp(s1, s2) == 0, s1, s2, "%s");  \
    free(s1); free(s2);                                 \
  } while (0)

#define EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, actual)  \
  do {                                                    \
    const char *s1 = expect;                              \
    char *s2 = actual;                                    \
    EXPECT_EQ_BASE(strcmp(s1, s2) == 0, s1, s2, "%s");    \
    free(s2);                                             \
  } while (0)

int testOutput(void) {
  printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count,
         test_pass * 100.0 / test_count);
  return test_main_ret;
}

#endif /* __TEST_H */
