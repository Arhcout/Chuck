#include <ECS.h>
#include <Error.h>

int main() {
  InitComponents();
  if (GetError() == ERROR_LV) {
    return 1;
  }
  Entity *a = CreateEntity();
  Transform *tr = AddComponent(a, Transform);
  tr->pos.x = 10;
  tr->pos.y = 10.12344;
  tr->scale.x = 10;
  tr->scale.y = 10.12344;
  tr->rotation = 14.43253;
  tr->layer = 10;
  UpdateSystems();
  return 0;
}
