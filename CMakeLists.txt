cmake_minimum_required(VERSION 3.18)
project(super_delete)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "src/*.*")

add_executable(super_delete ${SOURCES})

target_include_directories(super_delete PRIVATE "src")