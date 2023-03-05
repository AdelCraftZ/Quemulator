cmake_minimum_required(VERSION 3.24)
project(Quemulator)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED COMPONENTS random)

file(GLOB depends "src/*cpp" "src/*hpp*")
add_executable(quemulator ${depends})

target_include_directories(quemulator PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries(quemulator Boost::random)

if ((MSVC) AND (MSVC_VERSION GREATER_EQUAL 1914))
	target_compile_options(quemulator PUBLIC "/Zc:__cplusplus")
endif()
