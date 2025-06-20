#pragma once
#ifndef ROW_HPP
#define ROW_HPP

#include "Field.hpp"
#include <vector>

class Row {
private:
    std::vector<Field> fields;

public:
    Row();
    Row(const std::vector<Field>& fields);

    const std::vector<Field>& getFields() const;
    bool setFields(const std::vector<Field>& fields);
    bool setField(size_t index, const Field& field);

    const std::vector<Field>& getFields() const;
};

#endif