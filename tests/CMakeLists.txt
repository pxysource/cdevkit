cmake_minimum_required(VERSION 3.10)

project(TEST VERSION 1.0)  # 定义项目名称和版本

# 设置C++标准
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# FILE(GLOB ORIGIN *.c *.h)

# source_group()

# 添加源文件
set(PRIORITY_QUEUE_TEST_SOURCES priority_queue_test.c)

# 生成可执行文件
add_executable(priority_queue_test ${PRIORITY_QUEUE_TEST_SOURCES})

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/install/lib/cmake/)
find_package(cdevkit REQUIRED)
if (CDEVKIT_FOUND)
    message(STATUS "CDEVKIT_INCLUDE_DIR = ${CDEVKIT_INCLUDE_DIRS}")
    message(STATUS "CDEVKIT_LIBRARIES = ${CDEVKIT_LIBRARIES}")
    message(STATUS "CDEVKIT_LIB_DIR = ${CDEVKIT_LIBRARY_DIRS}")
endif ()
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
target_include_directories(priority_queue_test PUBLIC
    ${CDEVKIT_INCLUDE_DIRS}
)
target_link_directories(priority_queue_test PRIVATE
    ${CDEVKIT_LIBRARY_DIRS}
)
target_link_libraries(priority_queue_test PRIVATE
    cdevkit
)