#include "VM.h"
#include "Files.h"
#include "LCM/LuaCM.h"
#include "ScriptCmp.h"
#include "lauxlib.h"
#include <Error.h>
#include <lua.h>
#include <stdlib.h>

static lua_State *L;

void dumpstack(lua_State *L) {
  int top = lua_gettop(L);
  for (int i = 1; i <= top; i++) {
    LOG("%d\t%s\t\t", i, luaL_typename(L, i));
    switch (lua_type(L, i)) {
    case LUA_TNUMBER:
      fprintf(stderr, "%g\n", lua_tonumber(L, i));
      break;
    case LUA_TSTRING:
      fprintf(stderr, "%s\n", lua_tostring(L, i));
      break;
    case LUA_TBOOLEAN:
      fprintf(stderr, "%s\n", (lua_toboolean(L, i) ? "true" : "false"));
      break;
    case LUA_TNIL:
      fprintf(stderr, "%s\n", "nil");
      break;
    default:
      fprintf(stderr, "%p\n", lua_topointer(L, i));
      break;
    }
  }
  fputc('\n', stderr);
}

void InitVM() {
  L = luaL_newstate();
  if (!L) {
    ERROR("Can't initialize lua!\n");
    SetError(ERROR_LV);
    return;
  }
  luaL_openlibs(L);

  InitLCM(L);
}

void LoadScript(Script *script, Entity *e, const char *epath) {
  assert(script);
  assert(e);
  assert(epath);
  char *path = GetOSPath(epath);
  if (luaL_loadfile(L, path) != 0) {
    const char *error = lua_tostring(L, -1);
    ERROR("Can't load %s: %s\n", path, error);
    lua_pop(L, -1);
    free(path);
    return;
  }

  lua_getupvalue(L, -1, 1);
  if (!lua_istable(L, -1)) {
    ERROR("LUA ENV upvalue not a table (possible lua_State corruption)\n");
    SetError(ERROR_LV);
    return;
  }
  // setting _ENV
  lua_pushstring(L, "entity");
  lua_pushlightuserdata(L, e);

  lua_settable(L, -3);

  script->envRef = luaL_ref(L, LUA_REGISTRYINDEX);

  if (lua_pcall(L, 0, 1, 0) != LUA_OK) {
    const char *msg = lua_tostring(L, -1);
    ERROR("[LUA] %s\n", msg);
    SetError(ERROR_LV);
    return;
  }

  script->functionTableRef = luaL_ref(L, LUA_REGISTRYINDEX);
}

// TODO lua type checking

void RunScriptFn(Script *script, const char *fn) {
  lua_rawgeti(L, LUA_REGISTRYINDEX, script->envRef);
  lua_setupvalue(L, -1, 1);

  lua_rawgeti(L, LUA_REGISTRYINDEX, script->functionTableRef);
  lua_getfield(L, -1, fn);

  if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
    const char *msg = lua_tostring(L, -1);
    ERROR("[LUA] %s\n", msg);
    SetError(ERROR_LV);
    return;
  }
}

void UninitVM() {}
