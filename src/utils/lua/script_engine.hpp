#ifndef SCRIPT_ENGINE_HPP
#define SCRIPT_ENGINE_HPP

#include <sol/sol.hpp>

#include <iostream>
#include <optional>
#include <vector>

struct ScriptEngine
{
    ScriptEngine();

    bool runLuaScriptString(const std::string &script);
    bool runLuaScriptFile(const std::string &path);

    void addCallback(const char *name, std::vector<sol::function> &callbackL);

    sol::function getFunction(const char *functionName);

    template <typename T, typename... Args>
    std::optional<T> runFunctionSafe(const char *functionName, Args &&...args);

    template <typename... Args>
    auto addTable(const char *tName, Args &&...args);

    template <typename T, typename... Args>
    auto addType(const char *name, Args &&...args);

    template <typename T>
    auto addFunction(const char *name, T function);

    sol::state lua;
    sol::table gTable;

    private:
    void luaInitUtilApi();
};

template <typename T, typename... Args>
std::optional<T> ScriptEngine::runFunctionSafe(const char *functionName, Args &&...args)
{
    sol::protected_function func = gTable[functionName];
    sol::protected_function_result res = func(std::forward<Args>(args)...);

    if (res.valid())
    {
        T result = res;
        return result;
    }

    else
    {
        return {};
    }
}

template <typename T, typename... Args>
auto ScriptEngine::addType(const char* name, Args&&... args)
{
    return lua.new_usertype<T>(name, std::forward<Args>(args)...);
}

template <typename... Args>
auto ScriptEngine::addTable(const char* tableName, Args&&... args)
{
    return gTable.create_named(tableName, std::forward<Args>(args)...);
}

template <typename T>
auto ScriptEngine::addFunction(const char* name, T function)
{
    return gTable[name] = function;
}

template <typename... Args>
void runCallbacks(const std::vector<sol::function> &callbacks, Args &&...args)
{
    for (auto &callback : callbacks)
        callback(std::forward<Args>(args)...);
}

#endif