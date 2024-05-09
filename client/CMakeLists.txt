cmake_minimum_required(VERSION 3.29)
project(client VERSION 0.1.0 LANGUAGES C CXX)

find_package(raylib REQUIRED)

include_directories(client PRIVATE objects)

include(CTest)
enable_testing()

add_executable(client main.cpp
  objects/client.cpp
  objects/client.hpp
  )

target_link_libraries(client PRIVATE raylib)
target_compile_features(client PRIVATE cxx_std_11)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
