#pragma once

#include <stack>
#include <unordered_map>
#include <vector>
#include <string>

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
    void enter_scope();
    void exit_scope();
    void insert(const std::string &name, const T &type);
    T lookup(const std::string &name) const;
    bool exists(const std::string &name) const;

private:
    std::stack<std::unordered_map<std::string, T>> m_scopes;
};