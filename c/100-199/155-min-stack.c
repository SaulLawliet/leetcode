/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* strcmp() */
#include "c/data-structures/array.h"
#include "c/test.h"

typedef struct Node Node;
struct Node {
  int val;
  int min;
  Node *prev;
};

typedef struct {
  Node *top;
} MinStack;

/** initialize your data structure here. */

MinStack *minStackCreate() {
  MinStack *obj = malloc(sizeof(MinStack));
  obj->top = NULL;
  return obj;
}

void minStackPush(MinStack *obj, int x) {
  Node *node = malloc(sizeof(Node));
  node->val = x;
  if (obj->top == NULL) {
    node->prev = NULL;
    node->min = x;
  } else {
    node->prev = obj->top;
    node->min = obj->top->min < x ? obj->top->min : x;
  }
  obj->top = node;
}

void minStackPop(MinStack *obj) {
  if (obj->top != NULL) {
    Node *node = obj->top;
    obj->top = obj->top->prev;
    free(node);
  }
}

int minStackTop(MinStack *obj) {
  return obj->top != NULL ? obj->top->val : 0;
}

int minStackGetMin(MinStack *obj) {
  return obj->top != NULL ? obj->top->min : 0;
}

void minStackFree(MinStack *obj) {
  while (obj->top != NULL) {
    Node *node = obj->top;
    obj->top = node->prev;
    free(node);
  }
  free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, x);
 * minStackPop(obj);
 * int param_3 = minStackTop(obj);
 * int param_4 = minStackGetMin(obj);
 * minStackFree(obj);
*/

void test(char *expectStr, char *commandStr, char *argStr) {
  arrayEntry *expectEntry = arrayParse2D(expectStr, ARRAY_INT);
  arrayEntry *commandEntry = arrayParse1D(commandStr, ARRAY_STRING);
  arrayEntry *argEntry = arrayParse2D(argStr, ARRAY_INT);

  MinStack *obj;
  for (int i = 0; i < arraySize(commandEntry); i++) {
    char *command = ((char **)arrayValue(commandEntry))[i];
    int *arg = ((int **)arrayValue(argEntry))[i];
    int *expect = ((int **)arrayValue(expectEntry))[i];

    if (strcmp(command, "MinStack") == 0) {
      obj = minStackCreate();
    } else if (strcmp(command, "push") == 0) {
      minStackPush(obj, arg[0]);
    } else if (strcmp(command, "getMin") == 0) {
      EXPECT_EQ_INT(expect[0], minStackGetMin(obj));
    } else if (strcmp(command, "pop") == 0) {
      minStackPop(obj);
    } else if (strcmp(command, "top") == 0) {
      EXPECT_EQ_INT(expect[0], minStackTop(obj));
    } else if (strcmp(command, "free") == 0) {
      minStackFree(obj);
    }
  }
}

int main(void) {
  arrayParse1D("[]", ARRAY_INT);
  test("[[],[],[],[],[-3],[],[0],[-2]]",
       "[MinStack,push,push,push,getMin,pop,top,getMin]",
       "[[],[-2],[0],[-3],[],[],[],[]]");

  return testOutput();
}
