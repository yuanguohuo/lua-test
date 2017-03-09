#include <stdio.h>
#include <stdlib.h>

#include "sdump.h"

void dumpStack(lua_State * L, char * event)
{
  int num = lua_gettop(L);
  int i;

  fprintf(stdout, "\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
  fprintf(stdout, "%s\n",event);
  fprintf(stdout, "------------------------------------------------------------------\n");
  for(i=1; i<=num; i++)
  {
    int type = lua_type(L, i);
    switch(type)
    {
      case LUA_TSTRING:
        {
          fprintf(stdout, "%d:\t%s\t\t%s\n", i, lua_typename(L,type), lua_tostring(L,i));
          break;
        }
      case LUA_TBOOLEAN:
        {
          fprintf(stdout, "%d:\t%s\t\t%s\n", i, lua_typename(L,type), lua_toboolean(L,i)?"true":"false");
          break;
        }
      case LUA_TNUMBER:
        {
          fprintf(stdout, "%d:\t%s\t\t%g\n", i, lua_typename(L,type), lua_tonumber(L,i));
          break;
        }
      case LUA_TNIL:
        {
          fprintf(stdout, "%d:\t%s\t\t%s\n", i, lua_typename(L,type), "nil");
          break;
        }
      default:
        {
          fprintf(stdout, "%d:\t%s\t\t%s\n", i, lua_typename(L,type), "not-supported");
          break;
        }
    }
  }
  fprintf(stdout, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}
