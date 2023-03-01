cmake_minimum_required(VERSION 3.0)

project(wineman)

add_executable(wineman main.c outeffects.c)

target_include_directories(wineman PRIVATE ${CMAKE_CURRENT_DIR})

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSON-C REQUIRED json-c)

target_link_libraries(wineman PUBLIC ${JSON-C_LIBRARIES})
target_include_directories(wineman PUBLIC ${JSON-C_INDLUDE_DIRS})
