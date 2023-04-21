#pragma once

#include "nodes.hpp"
#include "visitor.hpp"
#include "semantic_exception.hpp"

class ErrorHandler
{
public:
    virtual int handle(const ProgramNode &ast) = 0;
    virtual void set_next(std::shared_ptr<ErrorHandler> next_handler) = 0;
};

class GenericErrorHandler : public ErrorHandler
{
public:
    GenericErrorHandler(std::shared_ptr<Visitor> checker) : m_next_handler(nullptr), m_checker(checker) {}

    int handle(ProgramNode &ast)
    {
        try
        {
            m_checker->visit(ast);
        }
        catch (const SemanticException &e)
        {
            std::cerr << "An error occured" << std::endl;
            return 1;
        }
    }

    void set_next(std::shared_ptr<ErrorHandler> next_handler) { m_next_handler = next_handler; }

private:
    std::shared_ptr<ErrorHandler> m_next_handler;
    std::shared_ptr<Visitor> m_checker;
};