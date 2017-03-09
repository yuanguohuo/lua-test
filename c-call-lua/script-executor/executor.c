#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include "sdump.h"

int load_script(lua_State * L, char * fname)
{
  int err = luaL_loadfile(L, fname);
  dumpStack(L, "after load file");
  if(0 != err)
  {
    fprintf(stdout, "%s\n", lua_tostring(L, -1));
    lua_pop(L, 1);
    return err;
  }
  return 0;
}

//table_pos is negative;
double get_double_field(lua_State * L, int table_pos, char * key)
{
  lua_pushstring(L, key);
  dumpStack(L, "get_double_filed, after push key");

  lua_gettable(L, table_pos - 1);  //pop the key and push the value;
  dumpStack(L, "get_double_filed, after gettable");
  if(!lua_isnumber(L, -1))
  {
    fprintf(stdout, "number expected, but it is %s\n", lua_typename(L,lua_type(L,-1)));
    return -1;  //-1 means error;
  }
  double ret = lua_tonumber(L, -1); //get the value;
  lua_pop(L,1);  //pop the value;

  dumpStack(L, "get_double_filed, after pop result");
  return ret;
}

double call_add(lua_State * L, double a1, double a2)
{
  lua_getglobal(L, "add");  //the function "add" is pushed on the top of the stack;

  luaL_checkstack(L, 2, "too many arguments"); //make sure we have 2 spaces in stack;

  lua_pushnumber(L, a1);
  lua_pushnumber(L, a2);
  dumpStack(L, "call_add: after get function and push args");

  if(lua_pcall(L, 2, 1, 0) != 0)
  {
    fprintf(stdout, "%s\n", lua_tostring(L, -1));
    lua_pop(L, 1);
    return -1;  //-1 means error;
  }
  dumpStack(L, "call_add: after pcall");

  if( !lua_isnumber(L, -1))
  {
    fprintf(stdout, "number expected, but we got %s\n", lua_typename(L, lua_type(L, -1)));
    lua_pop(L, 1);
    return -1;  //-1 means error;
  }

  double ret = lua_tonumber(L, -1);

  lua_pop(L, 1);
  dumpStack(L, "call_add: after pop result");
  
  return ret;
}

int main()
{
  lua_State * L = luaL_newstate();
  //lua_State * L1 = luaL_newstate();
  //lua_State * L2 = luaL_newstate();

  luaL_openlibs(L);

  if(0 != load_script(L, "test.lua"))
  {
    fprintf(stdout, "failed to load lua script\n");
    return 1;
  }

  int err = lua_pcall(L, 0, 0, 0); //execute the script;
  dumpStack(L, "after pcall");
  if(0 != err)
  {
    fprintf(stdout, "%s\n", lua_tostring(L, -1));
    lua_pop(L, 1);
    return err;
  }

  lua_getglobal(L, "width");  //ask lua to put width on the top of the stack;
  lua_getglobal(L, "hight");  //ask lua to put hight on the top of the stack;
  dumpStack(L, "after getglobal width and hight");
  if(!lua_isnumber(L, -2))
  {
    fprintf(stdout, "'width' is not a number\n");
    return 2;
  }
  if(!lua_isnumber(L, -1))
  {
    fprintf(stdout, "'hight' is not a number\n");
    return 2;
  }

  double width = lua_tonumber(L, -2);
  double hight = lua_tonumber(L, -1);

  fprintf(stdout, "width=%g, hight=%g\n", width, hight);

  lua_pop(L,2); //pop width and hight
  dumpStack(L, "after pop width and hight");


  lua_getglobal(L, "background");  //ask lua to put background at the top of the stack;

  dumpStack(L, "after getglobal background");

  if(!lua_istable(L, -1))
  {
    fprintf(stdout, "'background' is not a table\n");
    return 2;
  }

  double r = get_double_field(L, -1, "r");
  double g = get_double_field(L, -1, "g");
  double b = get_double_field(L, -1, "b");

  fprintf(stdout, "background: r=%g g=%g b=%g\n",r,g,b);

  lua_pop(L, 1); //pop the background table;
  dumpStack(L, "after pop background");


  //call function "add"
  double sum = call_add(L, 1.8, 3.5);
  dumpStack(L, "after call_add");

  fprintf(stdout, "sum=%g\n", sum);

  return 0;
}
