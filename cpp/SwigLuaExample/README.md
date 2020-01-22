# SwigLuaExample
Wanted to try [swig](http://swig.org/Doc1.3/Lua.html) with [Lua](https://www.lua.org/pil/24.html) following https://glennmccord.wordpress.com/2012/11/05/binding-c-to-lua-using-swig/

# Run

swig will build file `building_construction_wrap.cxx`

  swig -c++ -lua building-construction.i

  ExampleSwigLuaTable ../example.lua

# Resources

https://cmake.org/cmake/help/v3.0/module/FindLua.html

https://stackoverflow.com/questions/34704331/linux-c-lua-5-3-cmake-undefined-reference

- Error: *Found Lua: /usr/lib64/liblua5.1.so;/usr/lib64/libm.so (found version "5.3.2")*
- Solution: *find_package(Lua 5.3 REQUIRED)*
