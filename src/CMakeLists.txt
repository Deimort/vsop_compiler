FLEX_TARGET(SimpleLexer simpleLexer.lex ${CMAKE_CURRENT_BINARY_DIR}/simpleLexer.cpp COMPILE_FLAGS --header-file=${CMAKE_CURRENT_BINARY_DIR}/simpleLexer.hpp)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(Driver driver.cpp driver.hpp)

add_executable(${PROJECT_NAME} main.cpp ${FLEX_SimpleLexer_OUTPUTS} ${Driver})

target_link_libraries(${PROJECT_NAME} ${FLEX_LIBRARIES})