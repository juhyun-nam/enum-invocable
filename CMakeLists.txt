cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(invocation_binder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

enable_testing()
add_subdirectory(tests)
