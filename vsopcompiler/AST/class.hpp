#pragma once

#include <string>
#include <vector>
#include <memory>
#include "printer.hpp"
#include "field.hpp"
#include "method.hpp"

class ClassNode: public Printer {
public:
    ClassNode(const std::string& name, const std::string& parent = "Object")
        : m_name(name), m_parent(parent) {}

    void addField(std::unique_ptr<FieldNode> field) {
        m_fields.push_back(std::move(field));
    }

    void addMethod(std::unique_ptr<MethodNode> method) {
        m_methods.push_back(std::move(method));
    }

    std::string to_string() const override {
        Printer& printer = getPrinter();
        printer.setType("Class");
        printer.addString(m_name);
        printer.addString(m_parent);
        printer.addNodes(m_fields);
        printer.addNodes(m_methods);
        return printer.toString();
    }

private:
    std::string m_name;
    std::string m_parent;
    std::vector<std::unique_ptr<FieldNode>> m_fields;
    std::vector<std::unique_ptr<MethodNode>> m_methods;
};