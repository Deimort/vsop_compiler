FLEX_TARGET(Lexer lexer.lex ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp COMPILE_FLAGS)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(Tokens INTERFACE)
add_library(Lexer ${FLEX_Lexer_OUTPUTS})
target_include_directories(Lexer PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(Tokens INTERFACE tokens.hpp)