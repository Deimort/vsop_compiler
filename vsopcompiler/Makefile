CXX 			= g++

LLVM_CONFIG 	= llvm-config-11

CXXFLAGS 		= -Wall -Wextra -g -std=c++11 -O3 $(shell ${LLVM_CONFIG} --cxxflags) -fexceptions

LDFLAGS 		= $(shell ${LLVM_CONFIG} --ldflags --system-libs --libs all)

BISONFLAGS 		= -d

EXEC			= vsopc

SRC				= main.cpp \
				  driver.cpp \
				  parser.cpp \
				  lexer.cpp \
				  AST/nodes.cpp \
				  AST/type_checker.cpp

OBJ	  			= $(SRC:.cpp=.o)


all: $(EXEC)

main.o: driver.hpp parser.hpp

driver.o: driver.hpp parser.hpp AST/nodes.hpp

parser.o: driver.hpp parser.hpp AST/nodes.hpp

lexer.o: driver.hpp parser.hpp

AST/nodes.o: AST/visitor.hpp AST/nodes.hpp

AST/error_handler.o: AST/semantic_exception.hpp AST/visitor.hpp AST/nodes.hpp AST/error_handler.hpp

AST/type_checker.o: AST/symbol_exception.hpp AST/inheritance_exception.hpp AST/semantic_exception.hpp AST/symbol_table.hpp AST/nodes.hpp AST/visitor.hpp AST/type_checker.hpp

CG/code_generator.o: CG/scope_info.hpp CG/code_generator.hpp AST/nodes.hpp AST/visitor.hpp


$(EXEC): $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LDFLAGS) 

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
