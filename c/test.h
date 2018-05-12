/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#ifndef C_TEST_H_
#define C_TEST_H_

#include <stdio.h>  /* printf(), fprintf(), stderr */

static int test_main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

int testOutput(void) {
  printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count,
         test_pass * 100.0 / test_count);
  return test_main_ret;
}

struct TestTemp {
  union {
    struct { int a, b; } i;
    struct { double a, b; } d;
    struct { char *a, *b; } s;
    struct { const char *a, *b; } cs;
  };
};
static struct TestTemp test_temp;

#define EXPECT_EQ_BASE(equality, expect, actual, format)                \
  do {                                                                  \
    test_count++;                                                       \
    if (equality) {                                                     \
      test_pass++;                                                      \
    } else {                                                            \
      fprintf(stderr, "%s:%d: ", __FILE__, __LINE__);                   \
      fprintf(stderr, "\x1B[32mexpect: '" format "'\x1B[0m ", expect);  \
      fprintf(stderr, "\x1B[31mactual: '" format "'\x1B[0m\n", actual); \
      test_main_ret = 1;                                                \
    }                                                                   \
  } while (0)

#define EXPECT_EQ_INT(expect, actual)                                                   \
  do {                                                                                  \
    test_temp.i.a = (expect);                                                           \
    test_temp.i.b = (actual);                                                           \
    EXPECT_EQ_BASE(test_temp.i.a == test_temp.i.b, test_temp.i.a, test_temp.i.b, "%d"); \
  } while (0)

#define EXPECT_EQ_DOUBLE(expect, actual)                                                   \
  do {                                                                                     \
    test_temp.d.a = (expect);                                                              \
    test_temp.d.b = (actual);                                                              \
    EXPECT_EQ_BASE(test_temp.d.a == test_temp.d.b, test_temp.d.a, test_temp.d.b, "%.17g"); \
  } while (0)

#define EXPECT_EQ_STRING(expect, actual)                                                               \
  do {                                                                                                 \
    test_temp.cs.a = (expect);                                                                         \
    test_temp.cs.b = (actual);                                                                         \
    EXPECT_EQ_BASE(strcmp(test_temp.cs.a, test_temp.cs.b) == 0, test_temp.cs.a, test_temp.cs.b, "%s"); \
  } while (0)

#define EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, actual)                                             \
  do {                                                                                               \
    test_temp.cs.a = (expect);                                                                       \
    test_temp.s.b = (actual);                                                                        \
    EXPECT_EQ_BASE(strcmp(test_temp.cs.a, test_temp.s.b) == 0, test_temp.cs.a, test_temp.s.b, "%s"); \
    free(test_temp.s.b);                                                                             \
  } while (0)

#define EXPECT_EQ_STRING_AND_FREE(expect, actual)                                                  \
  do {                                                                                             \
    test_temp.s.a = (expect);                                                                      \
    test_temp.s.b = (actual);                                                                      \
    EXPECT_EQ_BASE(strcmp(test_temp.s.a, test_temp.s.b) == 0, test_temp.s.a, test_temp.s.b, "%s"); \
    free(test_temp.s.a);                                                                           \
    free(test_temp.s.b);                                                                           \
  } while (0)

#endif /* C_TEST_H_ */
