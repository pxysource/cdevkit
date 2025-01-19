cmake_minimum_required(VERSION 3.10)

project(CDEVKIT VERSION 0.1.0 LANGUAGES C)

set(EXPORT_NAME "cdevkit")

# 设置C++标准
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install CACHE PATH "Install path" FORCE)
add_definitions(-DCDEVKIT_LIBRARY)
option(CDEVKIT_BUILD_STATIC_LIB "Build static library" OFF)

FILE(GLOB ORIGIN *.h *.c)

source_group(include FILES ${ORIGIN}/*.h)

# 添加源文件
set(PROJECT_SOURCES
    ${ORIGIN}
)

if (CDEVKIT_BUILD_STATIC_LIB)
    set(LIB_TYPE "STATIC")
else ()
    set(LIB_TYPE "SHARED")
endif ()

add_library(${EXPORT_NAME} ${LIB_TYPE} ${PROJECT_SOURCES})

FILE(GLOB EXPORT_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
# target_include_directories(${EXPORT_NAME} PUBLIC
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/private>
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/DeveloperComponents>
#     $<INSTALL_INTERFACE:include>
# )

if (MINGW)
    set_target_properties(${EXPORT_NAME} PROPERTIES PREFIX "")
endif ()
if (MSVC)
    set_target_properties(${EXPORT_NAME} PROPERTIES DEBUG_POSTFIX "d")
endif ()

install(
    TARGETS ${EXPORT_NAME}
    EXPORT ${EXPORT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES ${EXPORT_HEADERS} DESTINATION include)
install(TARGETS ${EXPORT_NAME}
    RUNTIME DESTINATION ${CMAKE_BINARY_DIR}
)

set(INCLUDE_DIRS include)
set(LIBRARIES ${EXPORT_NAME})
set(LIB_DIR lib)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${PROJECT_BINARY_DIR}/${EXPORT_NAME}ConfigVersion.cmake
    VERSION 0.1.0
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/${EXPORT_NAME}Config.cmake.in
    ${PROJECT_BINARY_DIR}/${EXPORT_NAME}Config.cmake
    INSTALL_DESTINATION lib/cmake
    PATH_VARS INCLUDE_DIRS LIBRARIES LIB_DIR
    INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}
)

install(FILES ${PROJECT_BINARY_DIR}/${EXPORT_NAME}Config.cmake ${PROJECT_BINARY_DIR}/${EXPORT_NAME}ConfigVersion.cmake DESTINATION lib/cmake)