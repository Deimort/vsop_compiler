#pragma once

#include "nodes.hpp"
#include "visitor.hpp"
#include "semantic_exception.hpp"

class ErrorHandler
{
public:
    virtual int handle(ProgramNode &ast) = 0;
    virtual void set_next(std::shared_ptr<ErrorHandler> next_handler) = 0;
};

class GenericErrorHandler : public ErrorHandler
{
public:
    GenericErrorHandler(const std::string &source_file, std::shared_ptr<Visitor> checker) : m_checker(checker), m_source_file(source_file) {}

    int handle(ProgramNode &ast) override
    {
        try
        {
            m_checker->visit(ast);
            if (this->m_next_handler)
            {
                this->m_next_handler->handle(ast);
            }
            return 0;
        }
        catch (const SemanticException &e)
        {
            std::cerr << m_source_file << ":" << e.what() << std::endl;
            return 1;
        }
    }

    void set_next(std::shared_ptr<ErrorHandler> next_handler) override { m_next_handler = next_handler; }

private:
    std::shared_ptr<ErrorHandler> m_next_handler;
    std::shared_ptr<Visitor> m_checker;
    std::string m_source_file;
};