#pragma once

#include "mujs.h"
#include <map>
#include <string>

static double eval_string_to_double(const std::string &expr, const std::map<std::string, double> &vars = {})
{
    auto J = js_newstate(NULL, NULL, 0);

    js_atpanic(J, [](js_State *J) {
        auto text = js_tostring(J, -1);
        js_pop(J, 1);
        throw std::runtime_error(text);
    });

    if (!vars.empty())
    {
        js_newobject(J);
        for (auto &&[k, v] : vars)
        {
            js_pushnumber(J, v);
            js_setproperty(J, -2, k.c_str());
        }
        js_setglobal(J, "self");
    }

    js_loadstring(J, "[string]", expr.c_str());
    js_pushnumber(J, -1);
    js_call(J, 0);
    auto val = js_tonumber(J, -1);
    js_pop(J, 1);

    js_freestate(J);
    return val;
}

/** usage and test **
static void test()
{
    {
        auto val = eval_string_to_double("n=10;Math.pow(n,3)");
        std::cout << val << std::endl;
    }
    {
        auto val = eval_string_to_double("n=10;Math.pow(self.m,3)", { { "m", 11 } });
        std::cout << val << std::endl;
    }

    try
    {
        auto val = eval_string_to_double("error=10;Math.pow(n,3)");
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}
**/
