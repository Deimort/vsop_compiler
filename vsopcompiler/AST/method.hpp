#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "printer.hpp"
#include "formal.hpp"
#include "block.hpp"

class MethodNode : public Printer {
public:
    MethodNode(const std::string& name, std::vector<std::unique_ptr<FormalNode>> formals,
               const std::string& retType, std::unique_ptr<BlockNode> block)
        : m_name(name), m_formals(std::move(formals)), m_retType(retType), m_block(std::move(block)) {}

    std::string to_string() const override {
        Printer& printer = getPrinter();
        printer.setType("Method");
        printer.addString(m_name);
        printer.addNodes(m_formals);
        printer.addString(m_retType);
        printer.addString(m_block->to_string());
        return printer.toString();
    }

private:
    std::string m_name;
    std::vector<std::unique_ptr<FormalNode>> m_formals;
    std::string m_retType;
    std::unique_ptr<BlockNode> m_block;
};