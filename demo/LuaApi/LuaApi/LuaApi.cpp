// LuaApi.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#pragma comment(lib,"lua51.lib")
#pragma comment(lib,"luajit.lib")
#include <iostream>
extern "C" {
    #include<lua.h>
    #include<luajit.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

const char* lua_error_reason(int e) {
    if (e > 5) {
        return "Unknow error";
    }
    const char* desc[6] = {
        "LUA_OK",
        "LUA_YIELD",
        "LUA_ERRRUN",
        "LUA_ERRSYNTAX",
        "LUA_ERRMEM",
        "LUA_ERRERR"
    };
    return desc[e];
}

void check_error(lua_State * L, int e) {
    if (e == 0)return;
    std::cout<< lua_error_reason(e) <<":" << lua_tostring(L, -1) << std::endl;
}

int panic(lua_State* L) {
    std::cout << lua_tostring(L, -1);
    //lua_pop(L, 1);
    return 0;
}

//
//int pcall_callback_err_fun(lua_State* L)
//{
//    lua_Debug debug = {};
//    int ret = lua_getstack(L, 2, &debug); // 0是pcall_callback_err_fun自己, 1是error函数, 2是真正出错的函数
//    lua_getinfo(L, "Sln", &debug);
//
//    std::string err = lua_tostring(L, -1);
//    lua_pop(L, 1);
//    std::stringstream msg;
//    msg << debug.short_src << ":line " << debug.currentline;
//    if (debug.name != 0) {
//        msg << "(" << debug.namewhat << " " << debug.name << ")";
//    }
//
//    msg << " [" << err << "]";
//    lua_pushstring(L, msg.str().c_str());
//    return 1;
//}


static void stackDump(lua_State* L) {
    std::cout << "\nStack Start-------------------------------------" << std::endl;
    int i;
    int top = lua_gettop(L); //获取栈上元素个数
    for (i = 1; i <= top; i++) {
        int t = lua_type(L, i);
        switch (t) {
        case LUA_TSTRING: {
            printf("'%s'", lua_tostring(L, i));
            break;
        }
        case LUA_TBOOLEAN: {
            printf(lua_toboolean(L, i) ? "true" : "false");
            break;
        }
        case LUA_TNUMBER: { //TNUMBER包含两种类型 float和integer
            printf("%g", lua_tonumber(L, i));
            break;
        }
        default: {
            printf("%s", lua_typename(L, t));
            break;
        }
               printf("  ");
        }
        printf("\n");
    }
    std::cout << "Stack End---------------------------------------\n" << std::endl;
}

int myfun (lua_State* L) {
    std::cout << "my fun" << std::endl;
    return 0;
}
#define weak  
struct SS
{
    weak int * a;
};
int main()
{

    auto a = std::weak_ptr<std::string>();
    std::cout << sizeof(a)<< std::endl; //8 4 4

    lua_State *L=lua_open();
    luaL_openlibs(L);

    stackDump(L);
    lua_settop(L, 0);

    lua_atpanic(L, panic);

    int e=luaL_loadfile(L, "main.lua");
    check_error(L, e);

    //lua_getglobal(L, "Error");
    //int pos_err = lua_gettop(L);

    e = lua_pcall(L, 0, LUA_MULTRET, 0);
    check_error(L, e);

    lua_pushcfunction(L, myfun);
    lua_setglobal(L, "myfun");

    lua_getglobal(L, "Init");
    stackDump(L);
    e = lua_pcall(L, 0, 0,0);
    check_error(L, e);

   // lua_pop(L, 1);

    lua_getglobal(L, "Init");
    e = lua_pcall(L, 0, 0, 0);
    check_error(L, e);

    stackDump(L);
    std::cout << "Hello World!" << std::endl;
}
