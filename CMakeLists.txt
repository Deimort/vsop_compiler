cmake_minimum_required(VERSION 3.16.3)

# Set the project name and version
project(HelloWorld VERSION 1.0)

# Set the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Adds the compiler options
add_compile_options(-Wall -Wextra -Wmissing-prototypes -pedantic -DNDEBUG)
add_subdirectory(src)