#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "node.hpp"

class Printer {
public:
    virtual ~Printer() {}
    virtual std::string to_string() const = 0;
    void setType(const std::string& type);
    void addString(const std::string& str);
    void addNodes(const std::vector<std::unique_ptr<Node>>& nodes);
    std::string toString() const;
private:
    bool m_hasType = false;
    m_hasPrevious = false;
    std::stringstream m_buffer;
};