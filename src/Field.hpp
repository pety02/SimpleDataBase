#pragma once
#ifndef FIELD_HPP
#define FIELD_HPP

#include "FieldType.hpp"
#include <string>

class Field {
private:
    FieldType type;
    std::string rawValue; // Could be NULL, or actual string representation

public:
    Field();
    Field(FieldType type, const std::string& value);

    FieldType getType() const;
    std::string getValue() const;

    bool isNull() const;
    void setValue(const std::string& value);
    void setNull();
};

#endif