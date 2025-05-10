#pragma once
#ifndef COLUMN_HPP
#define COLUMN_HPP

#include "FieldType.hpp"
#include <vector>
#include <string>

class Column {
private:
FieldType type;
std::vector<std::string> values;

public:
Column(FieldType FieldType);
Column(FieldType FieldType, std::vector<std::string>values);

const FieldType getFieldType() const;
const std::vector<std::string> getValues() const;
};

#endif