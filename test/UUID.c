#include <Error.h>
#include <UUID.h>
#include <stdint.h>

int main() {
  uint64_t uuids[10];
  for (int i = 0; i < 10; i++) {
    uuids[i] = GenerateUUID();
    if (GetError() == ERROR_LV) {
      return i + 1;
    }
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (i == j)
        continue;
      if (uuids[i] == uuids[j]) {
        return -1;
      }
    }
  }
  return 0;
}
