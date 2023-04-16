#include <iostream>
#include <string>
#include <fstream>

#include "driver.hpp"

using namespace std;

enum class Mode
{
    LEX,
    PARSE,
    CHECK,
};

static const map<string, Mode> flag_to_mode = {
    {"-l", Mode::LEX},
    {"-p", Mode::PARSE},
    {"-c", Mode::CHECK},
};

int main(int argc, char const *argv[])
{

    Mode mode;
    string source_file;

    if (argc == 2)
    {
        mode = Mode::PARSE;
        source_file = argv[1];
    }
    else if (argc == 3)
    {
        if (flag_to_mode.count(argv[1]) == 0)
        {
            cerr << "Invalid mode: " << argv[1] << endl;
            return -1;
        }
        mode = flag_to_mode.at(argv[1]);
        source_file = argv[2];
    }
    else
    {
        cerr << "Usage: " << argv[0] << " [-l|-p] <source_file>" << endl;
        return -1;
    }

    VSOP::Driver driver = VSOP::Driver(source_file);

    int res;
    switch (mode)
    {
        case Mode::LEX:
            res = driver.lex();

            return res;

        case Mode::PARSE:
            res = driver.parse();

            if (res == 0)
            {
                driver.printAST();
            }

            return res;
        case Mode::CHECK:
            res = driver.check();

            if (res == 0)
            {
                res = driver.printAST();
            }

            return res;
    }


    return 0;
}