project(JsEval)

include_directories(Include/${PROJECT_NAME})
add_library(${PROJECT_NAME} STATIC Src/one.c)
target_include_directories(${PROJECT_NAME} PUBLIC Include)
