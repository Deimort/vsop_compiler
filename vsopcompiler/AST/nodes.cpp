#include "nodes.hpp"

void Serializer::setType(const std::string& type)
{
    m_hasType = true;
    m_buffer << type << "(";
}

void Serializer::addString(const std::string& str)
{
    if(m_hasPrevious) {
        if(m_inList) {
            m_buffer << ",\n";
        } else {
            m_buffer << ", ";
        }
    }

    m_buffer << str;
    m_hasPrevious = true;
}

void Serializer::startList() {
    if(m_hasPrevious) {
        m_buffer << ", ";
    }
    m_inList = true;
    m_hasPrevious = false;
    m_buffer << "[";
}

void Serializer::endList() {
    m_inList = false;
    m_hasPrevious = true;
    m_buffer << "]";
}

std::string Serializer::serialize() const {
    if (m_hasType) {
       m_buffer << ")";
    }
    std::string result = m_buffer.str();
    m_buffer.str("");
    return result;
}