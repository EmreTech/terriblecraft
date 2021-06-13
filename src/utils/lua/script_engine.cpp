#include "script_engine.hpp"

namespace
{

bool validScriptRun(const sol::protected_function_result &result)
{
    if (!result.valid())
    {
        sol::error err = result;
        std::cerr << "Error while running Lua script: " << err.what() << '\n';
    }
    return result.valid();
}

} // namespace

ScriptEngine::ScriptEngine()
: gTable(lua["game"].get_or_create<sol::table>())
{
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math, sol::lib::string);
    //luaInitUtilApi();
}

bool ScriptEngine::runLuaScriptString(const std::string &script)
{
    auto res = lua.script(script, [](auto L, auto res) {
        (void)L;
        return res;
    });

    return validScriptRun(res);
}

bool ScriptEngine::runLuaScriptFile(const std::string &path)
{
    auto script = lua.load_file(path);

    if (script.valid())
    {
        auto res = script();
        return validScriptRun(res);
    }

    else
    {
        sol::error err = script;
        std::cerr << "Error while trying to load Lua file at: " << path << ". Error: " << err.what() << '\n';
        return false;
    }

    return false;
}

sol::function ScriptEngine::getFunction(const char *functionName)
{
    return gTable[functionName];
}

void ScriptEngine::addCallback(const char *name, std::vector<sol::function> &callbacks)
{
    addFunction(name, [&callbacks](sol::function f){ 
        callbacks.push_back(f); 
    });
}