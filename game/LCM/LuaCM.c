#include "LuaCM.h"
#include "Input.h"
#include <ECS.h>
#include <Error.h>
#include <Time.h>
#include <UUID.h>
#include <VM.h>
#include <lauxlib.h>
#include <lua.h>

//////////////////////////////////////////////////////
/// ENTITY METHODS
//////////////////////////////////////////////////////

#define ENTITY_TNAME "lcm_mt_entity"

Entity *CheckEntity(lua_State *L, int idx) {
  Entity *entity = luaL_checkudata(L, idx, ENTITY_TNAME);
  if (!entity) {
    luaL_typeerror(L, idx, ENTITY_TNAME);
    return NULL;
  }
  return entity;
}

static int Entity_new(lua_State *L) {
  Entity *entity = CreateEntity();
  assert(entity);
  lua_pushlightuserdata(L, entity);
  return 1;
}

// args: num-type
static int Entity_HasComponent(lua_State *L) {
  Entity *e = CheckEntity(L, 1);
  lua_Integer type = luaL_checkinteger(L, 2);

  lua_pushboolean(L, HasComponent(e, type));
  return 1;
}

static int Entity_tostring(lua_State *L) {
  Entity *entity = CheckEntity(L, 1);
  lua_pushfstring(L, "%d", *entity);
  return 1;
}

static int Entity_gc(lua_State *L) {
  RemoveAllComponents(CheckEntity(L, 1));
  return 0;
}

//////////////////////////////////////////////////////
/// TRANSFORM METHODS
//////////////////////////////////////////////////////

// args: num x, num y
static int Transform_SetPosition(lua_State *L) {
  Entity *e = CheckEntity(L, 1);
  lua_Number x = luaL_checknumber(L, 2);
  lua_Number y = luaL_checknumber(L, 3);
  Transform *t = GetComponent(e, Transform);
  if (!t) {
    ERROR("Entity '%lu' doesn't have a transform component1\n", *e);
    return 0;
  }
  t->pos.x = x;
  t->pos.y = y;
  return 0;
}

// args: num scale_x, num scale_y
static int Transform_SetScale(lua_State *L) {
  Entity *e = CheckEntity(L, 1);
  lua_Number x = luaL_checknumber(L, 2);
  lua_Number y = luaL_checknumber(L, 3);
  Transform *t = GetComponent(e, Transform);
  if (!t) {
    ERROR("Entity '%lu' doesn't have a transform component1\n", *e);
    return 0;
  }
  t->scale.x = x;
  t->scale.y = y;
  return 0;
}

// args: num rotation
static int Transform_SetRotation(lua_State *L) {
  Entity *e = CheckEntity(L, 1);
  lua_Number rotation = luaL_checknumber(L, 2);
  Transform *t = GetComponent(e, Transform);
  if (!t) {
    ERROR("Entity '%lu' doesn't have a transform component1\n", *e);
    return 0;
  }
  t->rotation = rotation;
  return 0;
}

// args: int layer
static int Transform_SetLayer(lua_State *L) {
  Entity *e = CheckEntity(L, 1);
  lua_Integer layer = luaL_checknumber(L, 2);
  Transform *t = GetComponent(e, Transform);
  if (!t) {
    ERROR("Entity '%lu' doesn't have a transform component1\n", *e);
    return 0;
  }
  t->layer = layer;
  return 0;
}

// args: bool enable
static int Transform_SetEnable(lua_State *L) {
  Entity *e = CheckEntity(L, 1);
  bool enable = lua_toboolean(L, 2);
  Transform *t = GetComponent(e, Transform);
  if (!t) {
    ERROR("Entity '%lu' doesn't have a transform component1\n", *e);
    return 0;
  }
  t->enabled = enable;
  return 0;
}

static const struct luaL_Reg _LCM_EntityReg[] = {
    {"__tostring", Entity_tostring},
    {"__gc", Entity_gc},
    {"has_component", Entity_HasComponent},
    {"transform_set_position", Transform_SetPosition},
    {"transform_set_layer", Transform_SetLayer},
    {"transform_set_rotation", Transform_SetRotation},
    {"transform_set_scale", Transform_SetScale},
    {NULL, NULL},
};

//////////////////////////////////////////////////////
/// PUBLIC FUNCTIONS
//////////////////////////////////////////////////////

// no args
// return deltatime to lua
static int lf_GetDeltaTime(lua_State *L) {
  lua_pushnumber(L, e_deltaTime);
  return 1;
}

// no args
// return mouse pos in table: {x,y} to lua
static int lf_GetMousePos(lua_State *L) {
  Vecf2 pos;
  GetMousePosition(&pos);
  lua_createtable(L, 0, 2);
  lua_pushnumber(L, pos.x);
  lua_setfield(L, -2, "x");
  lua_pushnumber(L, pos.y);
  lua_setfield(L, -2, "y");
  return 1;
}

static const struct luaL_Reg _LCM_functions[] = {
    {"get_dt", lf_GetDeltaTime},
    {"get_mouse_pos", lf_GetMousePos},
    {"new_entity", Entity_new},
    {NULL, NULL},
};

void InitLCM(lua_State *L) {
  int i = 0;
  while (_LCM_functions[i].func != 0 && _LCM_functions[i].name != 0) {
    lua_pushcfunction(L, _LCM_functions[i].func);
    lua_setglobal(L, _LCM_functions[i].name);
    i++;
  }

  luaL_newmetatable(L, ENTITY_TNAME);
  luaL_setfuncs(L, _LCM_EntityReg, 0);
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");

  lua_pushlightuserdata(L, (void *)0xdeadbeef);
  lua_pushvalue(L, -2);
  lua_setmetatable(L, -2);
}
