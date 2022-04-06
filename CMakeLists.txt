cmake_minimum_required(VERSION 3.13)
project(info3-alg)

set(CMAKE_CXX_STANDARD 14)

option(CodeCoverage "CodeCoverage" OFF)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules/)
include(Coverage)

add_subdirectory(tp1)
add_subdirectory(tp2)
