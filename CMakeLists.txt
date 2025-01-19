cmake_minimum_required(VERSION 3.10)  # 设置CMake的最低版本

project(cdevkit VERSION 0.1 LANGUAGES C)  # 定义项目名称和版本

# 设置C++标准
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(BUILD_CDEVKIT_TEST FALSE CACHE BOOL "Build Test")

add_subdirectory(src)
if(BUILD_CDEVKIT_TEST)
    add_subdirectory(tests)
endif()