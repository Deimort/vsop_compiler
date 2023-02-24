/* This flex/bison example is provided to you as a starting point for your
 * assignment. You are free to use its code in your project.
 *
 * This example implements a simple calculator. You can use the '-l' flag to
 * list all the tokens found in the source file, and the '-p' flag (or no flag)
 * to parse the file and to compute the result.
 *
 * Also, if you have any suggestions for improvements, please let us know.
 */

#include <iostream>
#include <string>
#include <map>

#include "driver.hpp"
#include "simpleLexer.hpp"

using namespace std;
using namespace VSOP;

/**
 * @brief Print the information about a token
 *
 * @param token the token
 */
static void print_token(std::string token)
{
}

int Driver::lex()
{
    scan_begin();

    int error = 0;

    scan_end();

    return error;
}

void Driver::print_tokens()
{
    for (auto token : tokens)
        print_token(token);
}
