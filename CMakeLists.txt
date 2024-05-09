cmake_minimum_required(VERSION 3.29)
project(http-server VERSION 0.1.0 LANGUAGES C CXX)

find_package(raylib REQUIRED)

include_directories(http-server PRIVATE objects)

include(CTest)
enable_testing()

add_executable(http-server main.cpp
  )


target_link_libraries(http-server PRIVATE raylib)
target_compile_features(http-server PRIVATE cxx_std_11)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
