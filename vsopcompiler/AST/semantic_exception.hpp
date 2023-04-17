#pragma once

#include <exception>
#include <string>

class SemanticException : public std::exception
{
public:
    explicit SemanticException(const std::string &message) : m_message(message) {}

    const char *what() const noexcept override
    {
        return m_message.c_str();
    }

private:
    std::string m_message;
};