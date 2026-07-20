cmake_minimum_required(VERSION 3.14...3.22)
project(
  fix
  VERSION 0.1
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF) # avoid -Wpedantic and -std=c++20 and -std=gnu++20 conflicts

# -- Target -- #

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(fix
  ${sources}
)

target_include_directories(fix
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(fix
  PRIVATE
    -Wall
    -Wextra
    -Wno-comment
    -O1
)