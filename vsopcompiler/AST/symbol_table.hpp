#pragma once

#include <stack>
#include <unordered_map>
#include <vector>
#include <string>

#include "semantic_exception.hpp"

class FunctionType
{
public:
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
    void deactive();
    void active();
    void enter_scope();
    void exit_scope();
    void insert(const std::string &name, const T &type);
    T lookup(const std::string &name) const;
    bool exists(const std::string &name) const;

private:
    std::stack<std::unordered_map<std::string, T>> m_scopes;
    bool m_active = true;
};

template <class T>
void SymbolTable<T>::deactive()
{
    m_active = false;
}

template <class T>
void SymbolTable<T>::active() 
{
    m_active = true;
}

template <class T>
void SymbolTable<T>::enter_scope()
{
    m_scopes.push(std::unordered_map<std::string, T>());
}

template <class T>
void SymbolTable<T>::exit_scope()
{
    m_scopes.pop();
}

template <class T>
void SymbolTable<T>::insert(const std::string &name, const T &type)
{
    // Check if identifier is already bound in current scope
    auto it = m_scopes.top().find(name);
    if (it != m_scopes.top().end())
    {
        throw SemanticException("Identifier " + name + " already defined in current scope");
    }
    
    // Insert identifier in current scope
    m_scopes.top()[name] = type;
}

template <class T>
T SymbolTable<T>::lookup(const std::string &name) const
{
    if (!m_active)
        throw SemanticException("No such identifier: " + name);
    
    // search in current scope
    auto it = m_scopes.top().find(name);
    if (it != m_scopes.top().end())
    {
        return it->second;
    }

    // identifier not found in current scope, search in outer scopes
    for (auto i = m_scopes.size() - 1; i > 0; --i)
    {
        it = m_scopes.at(i).find(name);
        if (it != m_scopes.at(i).end())
        {
            return it->second;
        }
    }

    // identifier not found in any scope, throw error
    throw SemanticException("No such identifier: " + name);
}

template <class T>
bool SymbolTable<T>::exists(const std::string &name) const
{
    if (!m_active)
        return false;

    // search in current scope
    auto it = m_scopes.top().find(name);
    if (it != m_scopes.top().end())
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