cmake_minimum_required (VERSION 3.0)
project("cpp_exercises")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -Wall -Wextra -pedantic -Werror -Wnon-virtual-dtor")

include_directories(SYSTEM "${CMAKE_CURRENT_LIST_DIR}/catch")
include_directories(SYSTEM "${CMAKE_CURRENT_LIST_DIR}/sys")

add_executable(hello_world hello.cpp)

add_library(exercise_base STATIC
  sys/catch_main.cpp
  sys/utilities.cpp)

add_executable(module01
  module01_1.cpp
  module01_2.cpp
  module01_3.cpp)

target_link_libraries(module01 exercise_base)

add_executable(module02
  module02_1.cpp
  module02_2.cpp
  module02_3.cpp
  module02_4.cpp)

target_link_libraries(module02 exercise_base)

add_executable(module03
  module03_1.cpp
  module03_2.cpp
  module03_3.cpp)

target_link_libraries(module03 exercise_base)

add_executable(module04
  module04_1.cpp
  module04_2.cpp
  module04_3.cpp)

target_link_libraries(module04 exercise_base)
