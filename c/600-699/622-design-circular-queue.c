/*
 * Copyright (C) 2022, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 *   front
 *     |
 * [0, 1, 2]
 *        |
 *       rear
 *
 * 当队列为空的时候, front = -1, rear = -1;
 * 其他情况下, front 和 rear 均为对应的下标, 这样处理起来就会简单很多
 */

#include <stdbool.h>
#include "c/data-structures/array.h"
#include "c/test.h"

typedef struct {
  int *data;
  int size;
  int front;
  int rear;
} MyCircularQueue;

MyCircularQueue *myCircularQueueCreate(int k) {
  MyCircularQueue *obj = malloc(sizeof(MyCircularQueue));
  obj->data = malloc(sizeof(int) * k);
  obj->size = k;
  obj->front = -1;
  obj->rear = -1;
  return obj;
}

bool myCircularQueueIsEmpty(MyCircularQueue *obj) {
  return obj->front == -1 && obj->rear == -1;
}

bool myCircularQueueIsFull(MyCircularQueue *obj) {
  return (obj->rear + 1) % obj->size == obj->front;
}

bool myCircularQueueEnQueue(MyCircularQueue *obj, int value) {
  if (myCircularQueueIsFull(obj)) return false;

  if (obj->front == -1) {
    obj->front = 0;
    obj->rear = 0;
  } else {
    obj->rear = (obj->rear + 1) % obj->size;
  }
  obj->data[obj->rear] = value;
  return true;
}

bool myCircularQueueDeQueue(MyCircularQueue *obj) {
  if (myCircularQueueIsEmpty(obj)) return false;
  if (obj->front == obj->rear) {  // 移除最后一个的时候, 重置索引
    obj->front = -1;
    obj->rear = -1;
  } else {
    obj->front = (obj->front + 1) % obj->size;
  }
  return true;
}

int myCircularQueueFront(MyCircularQueue *obj) {
  if (myCircularQueueIsEmpty(obj)) return -1;
  return obj->data[obj->front];
}

int myCircularQueueRear(MyCircularQueue *obj) {
  if (myCircularQueueIsEmpty(obj)) return -1;
  return obj->data[obj->rear];
}

void myCircularQueueFree(MyCircularQueue *obj) {
  free(obj->data);
  free(obj);
}

void test(char *expectStr, char *commandStr, char *argStr) {
  arrayEntry *expectEntry = arrayParse1D(expectStr, ARRAY_STRING);
  arrayEntry *commandEntry = arrayParse1D(commandStr, ARRAY_STRING);
  arrayEntry *argEntry = arrayParse2D(argStr, ARRAY_INT);

  MyCircularQueue *obj;
  for (int i = 0; i < arraySize(commandEntry); i++) {
    char *expect = ((char **)arrayValue(expectEntry))[i];
    char *command = ((char **)arrayValue(commandEntry))[i];
    int *args = ((int **)arrayValue(argEntry))[i];

    if (strcmp(command, "MyCircularQueue") == 0) {  // Initializes the object with the size of the queue to be k.
      obj = myCircularQueueCreate(args[0]);
    } else if (strcmp(command, "Front") == 0) {  // Gets the front item from the queue. If the queue is empty, return -1.
      EXPECT_EQ_INT(atoi(expect), myCircularQueueFront(obj));
    } else if (strcmp(command, "Rear") == 0) {  // Gets the last item from the queue. If the queue is empty, return -1.
      EXPECT_EQ_INT(atoi(expect), myCircularQueueRear(obj));
    } else if (strcmp(command, "enQueue") == 0) {  // Inserts an element into the circular queue. Return true if the operation is successful.
      EXPECT_EQ_INT(strcmp(expect, "true") == 0, myCircularQueueEnQueue(obj, args[0]));
    } else if (strcmp(command, "deQueue") == 0) {  // Deletes an element from the circular queue. Return true if the operation is successful.
      EXPECT_EQ_INT(strcmp(expect, "true") == 0, myCircularQueueDeQueue(obj));
    } else if (strcmp(command, "isEmpty") == 0) {  // Checks whether the circular queue is empty or not.
      EXPECT_EQ_INT(strcmp(expect, "true") == 0, myCircularQueueIsEmpty(obj));
    } else if (strcmp(command, "isFull") == 0) {  // Checks whether the circular queue is full or not.
      EXPECT_EQ_INT(strcmp(expect, "true") == 0, myCircularQueueIsFull(obj));
    }
  }

  // 需要手动释放一下
  myCircularQueueFree(obj);

  arrayFree(expectEntry);
  arrayFree(commandEntry);
  arrayFree(argEntry);
}

int main(void) {
  test("[null, true, true, true, false, 3, true, true, true, 4]",
       "[MyCircularQueue, enQueue, enQueue, enQueue, enQueue, Rear, isFull, deQueue, enQueue, Rear]",
       "[[3], [1], [2], [3], [4], [], [], [], [4], []]");

  return testOutput();
}
