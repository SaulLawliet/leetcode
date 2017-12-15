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

#define EXPECT_EQ_BASE(equality, expect, actual, format)            \
  do {                                                              \
    test_count++;                                                   \
    if (equality) {                                                 \
      test_pass++;                                                  \
    } else {                                                        \
      fprintf(stderr, "%s:%s:%d:\t", __FILE__, __func__, __LINE__); \
      fprintf(stderr, "expect: " format " actual: " format "\n",    \
              expect, actual);                                      \
      test_main_ret = 1;                                            \
    }                                                               \
  } while (0)


void EXPECT_EQ_INT(int expect, int actual) {
  EXPECT_EQ_BASE(expect == actual, expect, actual, "%d");
}

void EXPECT_EQ_DOUBLE(double expect, double actual) {
  EXPECT_EQ_BASE(expect == actual, expect, actual, "%.17g");
}

void EXPECT_EQ_STRING(const char *expect, const char *actual) {
  EXPECT_EQ_BASE(strcmp(expect, actual) == 0, expect, actual, "%s");
}

void EXPECT_EQ_STRING_AND_FREE(char *expect, char *actual) {
  EXPECT_EQ_STRING(expect, actual);
  free(expect);
  free(actual);
}

void EXPECT_EQ_STRING_AND_FREE_ACTUAL(const char *expect, char *actual) {
  EXPECT_EQ_STRING(expect, actual);
  free(actual);
}

int testOutput(void) {
  printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count,
         test_pass * 100.0 / test_count);
  return test_main_ret;
}

#endif /* __TEST_H */
