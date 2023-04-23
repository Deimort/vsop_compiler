#pragma once

#include <exception>
#include <string>

class InheritanceException : public std::runtime_error
{
public:
    explicit InheritanceException(const std::string &message) : std::runtime_error(message) {}
};