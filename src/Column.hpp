#pragma once
#ifndef COLUMN_HPP
#define COLUMN_HPP

#include "Field.hpp"
#include <vector>

class Column {
private:
std::string name;
std::vector<Field> values;

public:
Column(const std::string& name);
Column(const std::string& name, const std::vector<Field>& values);

bool setName(const std::string& name);
bool setValues(const std::vector<Field>& values);

const std::string& getName() const;
const std::vector<Field>& getValues() const;
};

#endif