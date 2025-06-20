#pragma once
#ifndef FIELD_HPP
#define FIELD_HPP

#include "FieldType.hpp"
#include <exception>
#include <stdexcept>

class Field {
private:
    FieldType type;
    std::string rawValue; // Could be 'NULL', or actual string representation

public:
    Field();
    Field(const FieldType& type, const std::string& value);

    const FieldType& getType() const;
    const std::string getValue() const;

    bool isNull() const;
    bool setType(const FieldType& type);
    bool setValue(const std::string& value, const FieldType& type);
    bool setNull();
};

#endif