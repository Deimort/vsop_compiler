#pragma once

#include "nodes.hpp"
#include "visitor.hpp"
#include "semantic_exception.hpp"

class ErrorHandler
{
public:
    virtual int handle(const ProgramNode &ast) = 0;
    virtual std::shared_ptr<ErrorHandler> set_next(std::shared_ptr<ErrorHandler> next_handler) = 0;
};

class GenericErrorHandler : public ErrorHandler
{
public:
    GenericErrorHandler(std::shared_ptr<Visitor> checker) : m_next_handler(nullptr), m_checker(checker) {}

    int handle(const ProgramNode &ast)
    {
        try
        {
            m_checker->visit(ast);
        }
        catch (const SemanticException &e)
        {
            std::cerr << e->message() << std::endl;
            return 1;
        }
    }

private:
    std::shared_ptr<ErrorHandler> m_next_handler;
    std::shared_ptr<Visitor> m_checker;
};