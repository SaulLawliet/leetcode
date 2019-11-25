/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 维持一个有序的数组，二分查找，并插入
 */

#include <stdbool.h>
#include <stdlib.h> /* malloc(), free() */
#include "c/data-structures/array.h"
#include "c/test.h"

typedef struct {
  int start;
  int end;
} Interval;

typedef struct {
  Interval array[1001]; /* The number of calls to MyCalendar.book per test case will be at most 1000. */
  size_t length;
} MyCalendar;

MyCalendar *myCalendarCreate() {
  MyCalendar *obj = malloc(sizeof(MyCalendar));
  obj->length = 0;
  return obj;
}

void myCalendarFree(MyCalendar *obj) {
  free(obj);
}

bool myCalendarBook(MyCalendar *obj, int start, int end) {
  Interval interval; interval.start = start; interval.end = end;
  int a = 0, b = obj->length;
  while (a < b) {
    int i = (a + b) / 2;
    obj->array[i].start <= interval.start ? (a = i + 1) : (b = i);
  }

  if (a > 0 && obj->array[a-1].end > interval.start)
    return false;
  if (a < obj->length && obj->array[a].start < interval.end)
    return false;

  obj->length++;
  for (int i = obj->length; i > a; --i)
    obj->array[i] = obj->array[i-1];
  obj->array[a] = interval;
  return true;
}

/**
 * Your MyCalendar struct will be instantiated and called as such:
 * struct MyCalendar* obj = myCalendarCreate();
 * bool param_1 = myCalendarBook(obj, start, end);
 * myCalendarFree(obj);
 */

void test(const char *s) {
  MyCalendar *obj = myCalendarCreate();

  arrayEntry *entry = arrayParse2D(s, ARRAY_INT);
  for (int i = 0; i < arrayRow(entry); ++i) {
    int *array = ((int **)arrayValue(entry))[i];
    EXPECT_EQ_INT(array[0], myCalendarBook(obj, array[1], array[2]));
  }

  myCalendarFree(obj);
  arrayFree(entry);
}

int main(void) {
  test("[[1, 10, 20], [0, 15, 25], [1, 20, 30]]");

  return testOutput();
}
