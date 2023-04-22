#pragma once

#include <exception>
#include <string>

class SymbolException : public std::runtime_error
{
public:
    SymbolException(const std::string &message) : std::runtime_error(message) {}
};