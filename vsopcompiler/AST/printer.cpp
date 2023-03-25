#include "printer.hpp"

void Printer::setType(const std::string& type)
{
    m_hasType = true;
    m_buffer << type << "(";
}

void Printer::addString(const std::string& str)
{
    if(m_hasPrevious) {
        m_buffer << ", ";
    }

    m_buffer << str;
    m_hasPrevious = true;
}

void Printer::addNodes(const std::vector<std::unique_ptr<Node>>& nodes) {
    if(m_hasPrevious) {
        m_buffer << ", ";
    }

    m_buffer << "[";
    for (int i = 0; i < nodes.size(); i++) {
        m_buffer << nodes[i]->toString();
        if (i != nodes.size() - 1) {
            m_buffer << ", \n";
        }
    }
    m_buffer << "]";
    m_hasPrevious = true;
}

std::string Printer::toString() const {
    if (m_hasType) {
        m_buffer << ")"
    }
    std::string result = m_buffer.str();
    m_buffer.str("");
    return result;
}