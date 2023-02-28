CXX 			= g++

CXXFLAGS 		= -Wall -Wextra -g3 -std=c++11 -O3

BISONFLAGS 		= -d

EXEC			= vsopc

SRC				= main.cpp \
				  scanner.cpp \
				  tokens.cpp \
				  lexer.cpp

OBJ	  			= $(SRC:.cpp=.o)


all: $(EXEC)

main.o: scanner.hpp tokens.hpp

$(EXEC): $(OBJ)
	$(CXX) -o $@ $(LDFLAGS) $(OBJ)

lexer.o: scanner.cpp scanner.hpp tokens.hpp


lexer.cpp: lexer.lex
	flex $(LEXFLAGS) -o lexer.cpp $^
	

clean:
	@rm -f $(EXEC)
	@rm -f $(OBJ)
	@rm -f lexer.cpp

install-tools:
	@echo "Nothing to install."


.PHONY: clean
