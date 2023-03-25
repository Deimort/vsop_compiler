#pragma once

#include <string>
#include <iostream>
#include "printer.hpp"

class FieldNode: public Printer {
public:
    Field(const std::string& name, const std::string& type, const std::string& initExpr = "")
        : m_name(name), m_type(type), m_initExpr(initExpr) {}

    std::string to_string() const override {
        Printer& printer = getPrinter();
        printer.setType("Field");
        printer.addString(m_name);
        printer.addString(m_type);
        printer.addString(m_initExpr);
        return printer.toString();
    }

private:
    std::string m_name;
    std::string m_type;
    std::string m_initExpr;
};