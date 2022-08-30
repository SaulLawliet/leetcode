/*
 * Copyright (C) 2022, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 题目已经要求使用两个栈来实现队列, 然后时间复杂度均摊是 O(1)
 * 顺手拿出手边的扑克, 一顿模拟之后
 * 发现只要维持一个 push 状态 或 pop 状态, 当连续 push 或 连续 pop 的时候时间复杂度是O(1)
 */

#include <stdbool.h>
#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* strcmp() */
#include "c/data-structures/array.h"
#include "c/test.h"

typedef struct {
  int array[100];  // At most 100 calls will be made to push, pop, peek, and empty.
  int top;
} MyStack;

void myStackPush(MyStack *stack, int x) {
  stack->array[++stack->top] = x;
}

int myStackPop(MyStack *stack) {
  return stack->array[stack->top--];
}

int myStackPeek(MyStack *stack) {
  return stack->array[stack->top];
}

bool myStackEmpty(MyStack *stack) {
  return stack->top == -1;
}

// Stack end.

typedef struct {
  MyStack *push;
  MyStack *pop;
} MyQueue;

MyQueue *myQueueCreate() {
  MyQueue *queue = malloc(sizeof(MyQueue));
  queue->push = malloc(sizeof(MyStack));
  queue->push->top = -1;
  queue->pop = malloc(sizeof(MyStack));
  queue->pop->top = -1;
  return queue;
}

void switchForPush(MyQueue *obj) {
  while (!myStackEmpty(obj->pop)) {
    myStackPush(obj->push, myStackPop(obj->pop));
  }
}

void switchForPop(MyQueue *obj) {
  while (!myStackEmpty(obj->push)) {
    myStackPush(obj->pop, myStackPop(obj->push));
  }
}

void myQueuePush(MyQueue *obj, int x) {
  switchForPush(obj);
  myStackPush(obj->push, x);
}

int myQueuePop(MyQueue *obj) {
  switchForPop(obj);
  return myStackPop(obj->pop);
}

int myQueuePeek(MyQueue *obj) {
  switchForPop(obj);
  return myStackPeek(obj->pop);
}

bool myQueueEmpty(MyQueue *obj) {
  return myStackEmpty(obj->push) && myStackEmpty(obj->pop);
}

void myQueueFree(MyQueue *obj) {
  free(obj->push);
  free(obj->pop);
  free(obj);
}

void test(char *expectStr, char *commandStr, char *argStr) {
  arrayEntry *expectEntry = arrayParse1D(expectStr, ARRAY_STRING);
  arrayEntry *commandEntry = arrayParse1D(commandStr, ARRAY_STRING);
  arrayEntry *argEntry = arrayParse1D(argStr, ARRAY_STRING);

  MyQueue *obj;
  for (int i = 0; i < arraySize(commandEntry); i++) {
    char *expect = ((char **)arrayValue(expectEntry))[i];
    char *command = ((char **)arrayValue(commandEntry))[i];
    char *args = ((char **)arrayValue(argEntry))[i];

    if (strcmp(command, "MyQueue") == 0) {
      obj = myQueueCreate();
    } else if (strcmp(command, "push") == 0) {
      arrayEntry *e = arrayParse1D(args, ARRAY_INT);
      myQueuePush(obj, ((int *)arrayValue(e))[0]);
      arrayFree(e);
    } else if (strcmp(command, "pop") == 0) {
      EXPECT_EQ_INT(atoi(expect), myQueuePop(obj));
    } else if (strcmp(command, "peek") == 0) {
      EXPECT_EQ_INT(atoi(expect), myQueuePeek(obj));
    } else if (strcmp(command, "empty") == 0) {
      EXPECT_EQ_INT(strcmp("true", expect) == 0, myQueueEmpty(obj));
    }
  }

  myQueueFree(obj);

  arrayFree(argEntry);
  arrayFree(commandEntry);
  arrayFree(expectEntry);
}

int main(void) {
  test("[null, null, null, 1, 1, false]",
       "[MyQueue, push, push, peek, pop, empty]",
       "[[], [1], [2], [], [], []]");

  return testOutput();
}
