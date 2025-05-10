#pragma once
#ifndef TABLE_HPP
#define TABLE_HPP

#include "FieldType.hpp"
#include "Row.hpp"
#include <string>
#include <vector>

class Table {
private:
    std::string name;
    std::vector<std::string> columnNames;
    std::vector<FieldType> columnTypes;
    std::vector<Row> rows;

public:
    Table();
    Table(const std::string& name,
          const std::vector<std::string>& columnNames,
          const std::vector<FieldType>& columnTypes);

    const std::string& getName() const;
    const std::vector<Row>& getRows() const;
    const std::vector<std::string>& getColumnNames() const;
    const std::vector<FieldType>& getColumnTypes() const;

    void addRow(const Row& row);
    void addColumn(const std::string& name, FieldType type);
    bool modifyColumnType(size_t index, FieldType newType);

    // Other utility methods for update, delete, select...
};

#endif