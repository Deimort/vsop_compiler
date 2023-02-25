cmake_minimum_required(VERSION 3.18.4)

project(Compiler VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(FLEX REQUIRED)

add_subdirectory(src)
add_executable(${PROJECT_NAME} main.cpp ${FLEX_SimpleLexer_OUTPUTS})

target_link_libraries(${PROJECT_NAME} ${FLEX_LIBRARIES})