#include <stdio.h>
#include <string.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include "sdump.h"

int main()
{
  char buf[256];
  int err;
  lua_State * L = luaL_newstate();
  luaL_openlibs(L);


  //for test purpose, push some values into the stack, they are
  //useless;
  lua_pushboolean(L,0);
  lua_pushboolean(L,1);
  lua_pushnumber(L,10.58);
  lua_pushnil(L);
  lua_pushstring(L, "Hello, world");
  dumpStack(L);


  while(fgets(buf, sizeof(buf), stdin) != NULL)
  {
    //if success, put the compiled chunk on the stack;
    //if failure, put the error message on the stack and return err-code;
    err = luaL_loadbuffer(L, buf, strlen(buf), "line"); 

    dumpStack(L);

    if (err != 0)
    {
      //failure
      //get error message from stack;
      fprintf(stdout, "%s", lua_tostring(L,-1)); 
      lua_pop(L, 1);  //pop the error message;
    }
    else
    {
      //success
      //get the compiled chunk from stack and execute it;
      //if execution failure, put the error message on the stack;
      err = lua_pcall(L, 0, 0, 0);  

      dumpStack(L);

      if (err != 0)
      {
        fprintf(stdout, "%s", lua_tostring(L,-1)); //get the error message from the stack;
        lua_pop(L, 1);
      }
    }
  }

  lua_close(L);
  return 0;
}
