#pragma once

#ifdef _MSC_VER
    #pragma warning(push)
    #pragma warning(disable : 4200 4244 4576)
#endif

#include "quickjs.h"
#include <cassert>
#include <memory>
#include <optional>
#include <string_view>
#include <unordered_map>

class quickjs
{
public:
    quickjs()
        : runtime_(JS_NewRuntime())
        , context_(JS_NewContext(runtime_))
        , global_(JS_GetGlobalObject(context_))
    {
    }

    ~quickjs()
    {
        JS_FreeValue(context_, global_);
        if (context_ != nullptr)
        {
            JS_FreeContext(context_);
        }
        if (runtime_ != nullptr)
        {
            JS_FreeRuntime(runtime_);
        }
    }

public:
    void setVariables(std::string_view prop, const std::unordered_map<std::string, double> &vars)
    {
        if (vars.empty())
        {
            return;
        }

        auto root = global_;
        if (!prop.empty())
        {
            root = JS_NewObject(context_);
            JS_SetPropertyStr(context_, global_, prop.data(), root);
        }

        for (auto &&[k, v] : vars)
        {
            auto var = JS_NewFloat64(context_, v);
            int ret = JS_SetPropertyStr(context_, root, k.c_str(), var);
            assert(ret == TRUE);
        }
    }

    template <class T>
    std::optional<T> eval(const std::string_view &expr, const std::unordered_map<std::string, double> vars = {})
    {
        setVariables("self", vars);

        auto val = JS_Eval(context_, expr.data(), expr.size(), "", 0);
        switch (val.tag)
        {
        case JS_TAG_INT:
            return JS_VALUE_GET_INT(val);
        case JS_TAG_BOOL:
            return JS_VALUE_GET_BOOL(val);
        case JS_TAG_FLOAT64:
            return JS_VALUE_GET_FLOAT64(val);
        case JS_TAG_NULL:
        case JS_TAG_UNDEFINED:
        case JS_TAG_UNINITIALIZED:
        case JS_TAG_CATCH_OFFSET:
        case JS_TAG_EXCEPTION:
        default:
            return std::nullopt;
        }
    }

private:
    JSRuntime *runtime_{ nullptr };
    JSContext *context_{ nullptr };
    JSValue global_;
};

template <class T>
static std::optional<T> js_eval(const std::string_view &expr, const std::unordered_map<std::string, double> vars = {})
{
    quickjs qjs;
    return qjs.eval<T>(expr, vars);
}

#ifdef _MSC_VER
    #pragma warning(pop)
#endif
