CXX 			= g++

CXXFLAGS 		= -Wall -Wextra -g3 -std=c++11 -O3

BISONFLAGS 		= -d

EXEC			= vsopc

SRC				= main.cpp \
				  driver.cpp \
				  parser.cpp \
				  lexer.cpp \
				  AST/nodes.cpp

OBJ	  			= $(SRC:.cpp=.o)


all: $(EXEC)

main.o: driver.hpp parser.hpp

driver.o: driver.hpp parser.hpp AST/nodes.hpp

parser.o: driver.hpp parser.hpp AST/nodes.hpp

lexer.o: driver.hpp parser.hpp

AST/nodes.o: AST/nodes.hpp

$(EXEC): $(OBJ)
	$(CXX) -o $@ $(LDFLAGS) $(OBJ)

parser.cpp: parser.y
	bison $(BISONFLAGS) -o parser.cpp $^

parser.hpp: parser.y
	bison $(BISONFLAGS) -o parser.cpp $^

lexer.cpp: lexer.lex
	flex $(LEXFLAGS) -o lexer.cpp $^
	

clean:
	@rm -f $(EXEC)
	@rm -f $(OBJ)
	@rm -f lexer.cpp
	@rm -f parser.cpp parser.hpp location.hh

install-tools:
	@echo "Nothing to install."


.PHONY: clean
