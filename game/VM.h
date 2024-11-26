#pragma once
#include "ScriptCmp.h"
#include <lualib.h>

void InitVM();
void UninitVM();
void LoadScript(Script *script, Entity *e, const char *epath);
void RunScriptFn(Script *script, const char *fn);
#ifdef DEBUG
void dumpstack(lua_State *L);
#endif
