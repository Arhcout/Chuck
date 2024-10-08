#include "ECS.h"
#include <Error.h>

int main() {
  InitComponents();
  if (GetError() == ERROR_LV) {
    return 1;
  }
  UpdateSystems();
  return 0;
}
