#pragma once

#include <exception>
#include <string>

class InheritanceException : public std::runtime_error
{
public:
    InheritanceException(const std::string &message) : std::runtime_error(message) {}
};