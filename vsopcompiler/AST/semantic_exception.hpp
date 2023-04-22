#pragma once

#include <exception>
#include <string>

class SemanticException : public std::runtime_error
{
public:
    SemanticException(const int row, const int col, const std::string &message) : std::runtime_error(std::to_string(row) + ":" + std::to_string(col) + ": semantic error: " + message) {}
};