//
// Created by Damian Stewart on 31/12/16.
//

#ifndef OFAPP_LUAHELPERS_H
#define OFAPP_LUAHELPERS_H

#include <fmt/format.h>
#include "ofxLua.h"

namespace kll
{
    static void PushLuaArgs(lua_State *L)
    {
        return;
    }

    template<typename ... Types>
    void PushLuaArgs(lua_State *L, int first, Types ... rest)
    {
        lua_pushinteger(L, first);
        PushLuaArgs(L, rest...);
    }

    template<typename ... Types>
    void PushLuaArgs(lua_State *L, float first, Types ... rest)
    {
        lua_pushnumber(L, first);
        PushLuaArgs(L, rest...);
    }

    template<typename ... Types>
    void PushLuaArgs(lua_State *L, string first, Types ... rest)
    {
        lua_pushstring(L, first.c_str());
        PushLuaArgs(L, rest...);
    }

    template<typename ... Types>
    void PushLuaArgs(lua_State *L, bool first, Types ... rest)
    {
        lua_pushboolean(L, first);
        PushLuaArgs(L, rest...);
    }

    template<typename ... Types>
    bool CallLuaFunction(ofxLua *lua, string functionName, Types ... args)
    {
        if (!lua->isValid()) {
            fmt::print_colored(fmt::Color::RED, "Lua is not initialized\n");
            return false;
        }

        if (!lua->isFunction(functionName)) {
            fmt::print_colored(fmt::Color::RED, "Missing function {0}\n", functionName);
            return false;
        }

        lua_getglobal(*lua, functionName.c_str());
        PushLuaArgs(*lua, args...);

        auto result = lua_pcall(*lua, sizeof...(Types), 0, 0);
        if (result != 0) {
            fmt::print_colored(fmt::Color::RED, "Error calling {0}: {1}\n", functionName, (string) lua_tostring(*lua, -1));
            return false;
        }

        return true;
    }

}

#endif //OFAPP_LUAHELPERS_H
