/*
 * Copyright (C) 2017-2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include "data-structures/linked-list.h"
#include "test/test.h"

void testLinkedListRoundTrip(const char *str, int expectLength) {
  struct ListNode *list = linkedlistParse(str);

  EXPECT_EQ_INT(expectLength, linkedlistLength(list));
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(str, linkedlistToString(list));

  linkedlistFree(list);
}

int main(void) {
  testLinkedListRoundTrip("[]", 0);
  testLinkedListRoundTrip("[0]", 1);
  testLinkedListRoundTrip("[-2147483648,0,2147483647]", 3);

  return testOutput();
}
