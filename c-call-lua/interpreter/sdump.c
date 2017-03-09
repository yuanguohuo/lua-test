#include <stdio.h>

#include "sdump.h"

void dumpStack(lua_State * L)
{
  int num = lua_gettop(L);
  int i;

  printf("\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
  for(i=1; i<=num; i++)
  {
    int type = lua_type(L, i);
    switch(type)
    {
      case LUA_TSTRING:
        {
          printf("%d:\t%s\t\t%s\n", i, lua_typename(L,type), lua_tostring(L,i));
          break;
        }
      case LUA_TBOOLEAN:
        {
          printf("%d:\t%s\t\t%s\n", i, lua_typename(L,type), lua_toboolean(L,i)?"true":"false");
          break;
        }
      case LUA_TNUMBER:
        {
          printf("%d:\t%s\t\t%g\n", i, lua_typename(L,type), lua_tonumber(L,i));
          break;
        }
      case LUA_TNIL:
        {
          printf("%d:\t%s\t\t%s\n", i, lua_typename(L,type), "nil");
          break;
        }
      default:
        {
          printf("%d:\t%s\t\t%s\n", i, lua_typename(L,type), "not-supported");
          break;
        }
    }
  }
  printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}
