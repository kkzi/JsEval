cmake_minimum_required(VERSION 3.10)
project(quickjs)

set(quickjs_version 2020-07-05)
set(quickjs_sources
    quickjs.c
    utils/libregexp.c
    utils/libunicode.c
    utils/libbf.c
    utils/cutils.c
    libc/quickjs-libc.c
)

add_library(${PROJECT_NAME} STATIC ${quickjs_sources} )
target_compile_definitions(${PROJECT_NAME} PRIVATE CONFIG_VERSION="${quickjs_version}")
