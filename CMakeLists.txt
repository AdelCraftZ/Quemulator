cmake_minimum_required(VERSION 3.24)
project(Quemulator)

set(CMAKE_CXX_STANDARD 17)

file(GLOB depends "src/*cpp" "src/*hpp*")
add_executable(Quemulator ${depends})
