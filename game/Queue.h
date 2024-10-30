#pragma once
#include <stddef.h>

typedef struct Queue_s {
  void *data;
  size_t back, front;
  size_t len, maxLen, objSize;
} Queue;

Queue *CreateQueue(size_t objSize, size_t baseSize);
void DestroyQueue(Queue *queue);

// make a deep copy of obj
void Enqueue(Queue *queue, const void *obj);
// returns a new object
void *Dequeue(Queue *queue);
