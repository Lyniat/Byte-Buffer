cmake_minimum_required(VERSION 3.22)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(THIS_PROJECT_NAME "byte-buffer")

project(${THIS_PROJECT_NAME} LANGUAGES C CXX)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS src/*.cpp)

include_directories(include)

add_library(${THIS_PROJECT_NAME} STATIC ${SRC})

set_property(TARGET ${THIS_PROJECT_NAME} PROPERTY CXX_STANDARD 17)

set_target_properties(${THIS_PROJECT_NAME} PROPERTIES OUTPUT_NAME "bytebuffer")

if (WIN32)
    if(NOT MSVC)
        target_compile_options(${THIS_PROJECT_NAME} PUBLIC -fPIC -fno-rtti -fno-exceptions -Wno-deprecated-enum-enum-conversion)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    endif()
elseif (APPLE)
    target_compile_options(${THIS_PROJECT_NAME} PUBLIC -fPIC -fno-rtti -fno-exceptions)
elseif (UNIX)
    target_compile_options(${THIS_PROJECT_NAME} PUBLIC -fPIC -fno-rtti -fno-exceptions)
endif ()

if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /MT")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

set(CMAKE_SKIP_RPATH ON)

# https://discourse.cmake.org/t/installing-headers-the-modern-way-regurgitated-and-revisited/3238/3
target_sources(${THIS_PROJECT_NAME} PUBLIC
        FILE_SET public_headers
        TYPE HEADERS
        BASE_DIRS include
        FILES
        include/bytebuffer/buffer.h
        include/bytebuffer/memory.h
)

install(TARGETS ${THIS_PROJECT_NAME} FILE_SET public_headers)

include(CTest)

add_executable(test_01 test/test_01.cpp)
set_property(TARGET test_01 PROPERTY CXX_STANDARD 17)
target_link_libraries(test_01 ${THIS_PROJECT_NAME})
add_test(NAME "Test 1"
        COMMAND test_01)

add_executable(test_02 test/test_02.cpp)
set_property(TARGET test_02 PROPERTY CXX_STANDARD 17)
target_link_libraries(test_02 ${THIS_PROJECT_NAME})
add_test(NAME "Test 2"
        COMMAND test_02)

add_executable(test_03 test/test_03.cpp)
set_property(TARGET test_03 PROPERTY CXX_STANDARD 17)
target_link_libraries(test_03 ${THIS_PROJECT_NAME})
add_test(NAME "Test 3"
        COMMAND test_03)

add_executable(test_04 test/test_04.cpp)
set_property(TARGET test_04 PROPERTY CXX_STANDARD 17)
target_link_libraries(test_04 ${THIS_PROJECT_NAME})
add_test(NAME "Test 4"
        COMMAND test_04)
