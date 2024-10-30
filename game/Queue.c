#include "Queue.h"
#include <Error.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

Queue *CreateQueue(size_t objSize, size_t baseSize) {
  assert(baseSize != 0);
  assert(objSize != 0);
  Queue *queue = malloc(sizeof(Queue));
  MALLOC_CHECK(queue, NULL);

  queue->objSize = objSize;
  queue->maxLen = baseSize;
  queue->len = 0;
  queue->data = malloc(objSize * baseSize);
  if (!queue->data) {
    ERROR("malloc error\n");
    SetError(ERROR_LV);
    free(queue);
    return NULL;
  }
  queue->back = -1;
  queue->front = 0;
  return queue;
}

void DestroyQueue(Queue *queue) {
  assert(queue);
  free(queue->data);
  free(queue);
}

static void Grow(Queue *queue) {
  assert(queue);
  queue->maxLen *= 2;
  queue->data = realloc(queue->data, queue->maxLen * queue->objSize);
}

// make a deep copy of obj
void Enqueue(Queue *queue, const void *obj) {
  assert(queue);
  assert(obj);

  if (queue->len == queue->maxLen) {
    Grow(queue);
  }

  if (queue->back == queue->maxLen - 1) {
    queue->back = -1;
  }
  queue->back++;
  memcpy(queue->data + queue->back * queue->objSize, obj, queue->objSize);
  queue->len++;
}

// returns a new object
void *Dequeue(Queue *queue) {
  if (queue->len == 0) {
    return NULL;
  }
  void *out = malloc(queue->objSize);
  MALLOC_CHECK(out, NULL);
  memcpy(out, queue->data + queue->front * queue->objSize, queue->objSize);
  queue->front++;
  if (queue->front == queue->maxLen) {
    queue->front = 0;
  }
  queue->len--;
  return out;
}
