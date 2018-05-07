/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#ifndef C_TOOLS_QUEUE_H_
#define C_TOOLS_QUEUE_H_

#include <stdbool.h>

#ifndef QUEUE_INIT_SIZE
#define QUEUE_INIT_SIZE 64
#endif

struct Queue {
  int front, rear, size;
  void **array;
};

struct Queue *queueMake();
void queueFree(struct Queue *q);

bool queueIsEmpty(struct Queue *q);
void queueOffer(struct Queue *q, void *e);
void *queuePoll(struct Queue *q);

#endif /* C_TOOLS_QUEUE_H_ */
