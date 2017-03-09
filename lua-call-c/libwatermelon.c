#include <stdio.h>
#include <dirent.h>
#include <math.h>

#include <errno.h>
#include <string.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int l_dir(lua_State * L)
{
  fprintf(stdout, "Enter l_dir, L=%p\n", L);

  DIR * dir;
  struct dirent * entry;
  int i;

  const char * path = luaL_checkstring(L, 1);

  dir = opendir(path);
  if(dir == NULL)
  {
    lua_pushnil(L);
    lua_pushstring(L, strerror(errno));
    return 2;
  }

  lua_newtable(L);
  i = 1;
  while((entry=readdir(dir)) != NULL)
  {
    lua_pushnumber(L, i++);
    lua_pushstring(L, entry->d_name);
    lua_settable(L, -3);
  }

  closedir(dir);
  return 1;
}

static int l_sin(lua_State * L)
{
  fprintf(stdout, "Enter l_sin, L=%p\n", L);
  double d = luaL_checknumber(L, 1);
  lua_pushnumber(L, sin(d));
  return 1;
}

static const struct luaL_Reg libfunctions[] = 
{
  {"watermelondir", l_dir},
  {"watermelonsin", l_sin},
  {NULL, NULL}
};

int luaopen_libwatermelon(lua_State * L)
{
  luaL_register(L, "libwatermelon", libfunctions);
  return 1;
}
