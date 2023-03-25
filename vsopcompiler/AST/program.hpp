#pragma once

#include <vector>
#include <memory>
#include "class.hpp"
#include "printer.hpp"

class ProgramNode : public Printer {
public:
    void addClass(std::unique_ptr<ClassNode> classNode) {
        m_classes.push_back(std::move(classNode));
    }

    std::string to_string() const override {
        addNodes(m_classes);
        return toString();
    }

private:
    std::vector<std::unique_ptr<ClassNode>> m_classes;
};