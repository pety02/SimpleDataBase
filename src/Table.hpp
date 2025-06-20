#pragma once
#ifndef TABLE_HPP
#define TABLE_HPP

#include "Row.hpp"
#include "Column.hpp"

class Table {
private:
    std::string name;
    std::vector<std::string> columnNames;
    std::vector<FieldType> columnTypes;
    std::vector<Row> rows;

public:
    Table(std::string name);
    Table(const std::string& name,
          const std::vector<std::string>& columnNames,
          const std::vector<FieldType>& columnTypes);

    const std::string& getName() const;
    const std::vector<Row>& getRows() const;
    const std::vector<Column>& getColumns() const;
    const std::vector<std::string>& getColumnNames() const;
    const std::vector<FieldType>& getColumnTypes() const;

    bool setName(const std::string& name);
    bool setColumnNames(const std::vector<std::string>& columnNames);
    bool setColumnTypes(const std::vector<FieldType>& columnTypes);
    bool setRows(const std::vector<Row>& rows);

    void addRow(const Row& row);
    void addColumn(const std::string& name, FieldType type);
    bool modifyColumnType(size_t index, FieldType newType);

private:
    // Other utility methods for update, delete, select if they are needed...
};

#endif