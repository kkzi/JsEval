
demo.cpp

```c++
#include "quickjs/quickjs.hpp"
#include <iostream>
#include <string>

static void simple_test()
{
    auto runtime = JS_NewRuntime();
    auto ctx = JS_NewContext(runtime);

    std::string test("i=10;10*i");
    auto val = JS_Eval(ctx, test.c_str(), test.size(), "", 0);
    auto i = JS_VALUE_GET_INT(val);

    JS_FreeValue(ctx, val);
    JS_FreeContext(ctx);
    JS_FreeRuntime(runtime);

    std::cout << i << std::endl;
}

static void test()
{
    {
        auto val = js_eval<double>("i=10;10*i");
        std::cout << *val << std::endl;
    }

    {
        auto val = js_eval<double>("var a=10;Math.pow(a,2) + self.hello*1000", { {"hello",123},{"world",456} });
        std::cout << *val << std::endl;
    }
}

int main()
{
    test();
}

```
