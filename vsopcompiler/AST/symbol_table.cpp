#include "symbol_table.hpp"

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
    m_scopes.top()[name] = type;
}

template <class T>
T SymbolTable<T>::lookup(const std::string &name) const
{
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