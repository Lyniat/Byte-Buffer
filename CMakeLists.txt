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
        include/bytebuffer/ByteBuffer.h
        include/bytebuffer/ReadBuffer.h
        include/bytebuffer/memory.h
)

install(TARGETS ${THIS_PROJECT_NAME} FILE_SET public_headers)

option(BUILD_TESTING "Byte Buffer tests" ON)
if (BUILD_TESTING)
    enable_testing()

    add_executable(test_bb_01 test/test_01.cpp)
    target_link_libraries(test_bb_01 ${THIS_PROJECT_NAME})
    add_test(NAME "Test Byte Buffer 1"
            COMMAND test_bb_01)

    add_executable(test_bb_02 test/test_02.cpp)
    target_link_libraries(test_bb_02 ${THIS_PROJECT_NAME})
    add_test(NAME "Test Byte Buffer 2"
            COMMAND test_bb_02)

    add_executable(test_bb_03 test/test_03.cpp)
    target_link_libraries(test_bb_03 ${THIS_PROJECT_NAME})
    add_test(NAME "Test Byte Buffer 3"
            COMMAND test_bb_03)

    add_executable(test_bb_04 test/test_04.cpp)
    target_link_libraries(test_bb_04 ${THIS_PROJECT_NAME})
    add_test(NAME "Test Byte Buffer 4"
            COMMAND test_bb_04)

    add_executable(test_bb_05 test/test_05.cpp)
    target_link_libraries(test_bb_05 ${THIS_PROJECT_NAME})
    add_test(NAME "Test Byte Buffer 5"
            COMMAND test_bb_05)

    add_executable(test_bb_06 test/test_06.cpp)
    target_link_libraries(test_bb_06 ${THIS_PROJECT_NAME})
    add_test(NAME "Test Byte Buffer 6"
            COMMAND test_bb_06)

    add_executable(test_bb_07 test/test_07.cpp)
    target_link_libraries(test_bb_07 ${THIS_PROJECT_NAME})
    add_test(NAME "Test Byte Buffer 7"
            COMMAND test_bb_07)

    set_target_properties(test_bb_01 test_bb_02 test_bb_03 test_bb_04 test_bb_05 test_bb_06 test_bb_07
            PROPERTIES CXX_STANDARD 17
            COMPILE_WARNING_AS_ERROR ON)
endif()