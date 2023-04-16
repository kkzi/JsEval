#include "quickjs.h"
#include <iostream>
#include <string>

int main()
{
    auto runtime = JS_NewRuntime();
    auto ctx = JS_NewContext(runtime);

    std::string test("i=10;Math.pow(i, 3)");
    auto val = JS_Eval(ctx, test.c_str(), test.size(), "", 0);
    auto i = JS_VALUE_GET_INT(val);
    std::cout << i << std::endl;

    JS_FreeValue(ctx, val);
    JS_FreeContext(ctx);
    JS_FreeRuntime(runtime);
    std::cout << "helloworld" << std::endl;
}
