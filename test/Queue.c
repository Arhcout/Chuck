#include <Error.h>
#include <Queue.h>
#include <stdlib.h>

int main() {
  Queue *queue = CreateQueue(sizeof(int), 2);
  if (GetError() == ERROR_LV) {
    return 1;
  }
  for (int i = 0; i < 10; i++) {
    Enqueue(queue, &i);
  }
  for (int i = 0; i < 10; i++) {
    int *n = Dequeue(queue);
    if (!n) {
      return 2;
    }
    LOG("%d: %d\n", i, *n);
    free(n);
  }
  DestroyQueue(queue);
  return 0;
}
