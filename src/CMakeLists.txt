FLEX_TARGET(SimpleLexer simpleLexer.lex ${CMAKE_CURRENT_BINARY_DIR}/simpleLexer.cpp COMPILE_FLAGS --header-file=${CMAKE_CURRENT_BINARY_DIR}/simpleLexer.hpp)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
