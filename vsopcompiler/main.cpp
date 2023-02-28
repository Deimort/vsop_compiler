#include <iostream>
#include <string>
#include <fstream>
#include "scanner.hpp"
#include "tokens.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " -l input_file\n";
        return 1;
    }

    if (std::string(argv[1]) != "-l")
    {
        std::cerr << "Error: invalid option '" << argv[1] << "'\n";
        return 1;
    }
    std::ifstream inputFile(argv[2]);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: could not open input file '" << argv[1] << "'\n";
        return 1;
    }

    Scanner lexer(&inputFile, argv[2]);
    auto tokens = lexer.scan();

    if(lexer.hasErrorOccured()) {
        return 1;
    }

    for (auto token : tokens) {
        std::cout << token.to_string() << std::endl;
    }

    return 0;
}