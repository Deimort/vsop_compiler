#pragma once

#include <deque>
#include <unordered_map>
#include <vector>
#include <string>

#include "semantic_exception.hpp"

class FunctionType
{
public:
    FunctionType() = default;
    FunctionType(const std::string &return_type, const std::vector<std::string> &parameter_types)
        : m_return_type(return_type), m_parameter_types(parameter_types) {}

    const std::string &return_type() const { return m_return_type; }
    const std::vector<std::string> &parameter_types() const { return m_parameter_types; }

private:
    std::string m_return_type;
    std::vector<std::string> m_parameter_types;
};

template <class T>
class SymbolTable
{
public:
    void deactive()
    {
        m_active = false;
    }

    void active()
    {
        m_active = true;
    }

    void enter_scope()
    {
        m_scopes.push_front(std::unordered_map<std::string, T>());
    }

    void exit_scope()
    {
        m_scopes.pop_front();
    }

    void insert(const std::string &name, const T &type)
    {
        // Check if identifier is already bound in current scope
        auto it = m_scopes.front().find(name);
        if (it != m_scopes.front().end())
            throw SemanticException("Identifier " + name + " already defined in current scope");

        // Insert identifier in current scope
        m_scopes.front()[name] = type;
    }

    T lookup(const std::string &name) const
    {
        if (!m_active)
            throw SemanticException("No such identifier: " + name);

        // search in current scope
        auto it = m_scopes.front().find(name);
        if (it != m_scopes.front().end())
            return it->second;

        // identifier not found in current scope, search in outer scopes
        for (auto i = m_scopes.size() - 1; i > 0; --i)
        {
            it = m_scopes.at(i).find(name);
            if (it != m_scopes.at(i).end())
                return it->second;
        }

        // identifier not found in any scope, throw error
        throw SemanticException("No such identifier: " + name);
    }

    bool exists(const std::string &name) const
    {
        if (!m_active)
            return false;

        // search in current scope
        auto it = m_scopes.front().find(name);
        if (it != m_scopes.front().end())
        {
            return true;
        }

        // identifier not found in current scope, search in outer scopes
        for (auto i = m_scopes.size() - 1; i > 0; --i)
        {
            it = m_scopes.at(i).find(name);
            if (it != m_scopes.at(i).end())
            {
                return true;
            }
        }

        // identifier not found in any scope
        return false;
    }

private:
    std::deque<std::unordered_map<std::string, T>> m_scopes;
    bool m_active = true;
};