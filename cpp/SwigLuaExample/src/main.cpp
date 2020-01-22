#include <iostream>
#include "Skyscraper.hpp"

#include <lua5.3/lua.hpp>

extern "C" {

int luaopen_building_construction(lua_State *L); // declare the wrapped module

}

//static void readTable(float values[], int len) {
//
//    for (int i = 0; i < len; ++i)
//        printf("VALUE : %g", values[i]);
//}

#define LUA_EXTRALIBS {"building_construction",luaopen_building_construction}

int main(int argc, const char *argv[]) {
    lua_State *L;
    if (argc < 2) {
        printf("%s: <filename.lua>\n", argv[0]);
        return 0;
    }

    L = luaL_newstate();
    luaopen_base(L);  // load basic libs (eg. print)
    luaL_openlibs(L); // load all the lua libs (gives us math string functions etc.)
    luaopen_building_construction(L);   // load the wrapped module
    if (luaL_loadfile(L, argv[1]) == 0) // load and run the file
        lua_pcall(L, 0, 0, 0);
    else
        printf("unable to load %s\n", argv[1]);
    lua_close(L);
    return 0;
}