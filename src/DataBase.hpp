#pragma once
#ifndef DATA_BASE_HPP
#define DATA_BASE_HPP

#include "Table.hpp"
#include "Utils.hpp"

class DataBase {
private:
std::string name;
std::vector<Table> tables;

public:
DataBase(const std::string& name);
DataBase(const std::string& name, std::vector<Table> tables);

bool setName(const std::string& name);
bool setTables(const std::vector<Table>& tables);

const std::string& getName() const;
const std::vector<Table> getTables() const;

std::vector<std::string> showTables();
std::vector<std::string> describe(const std::string& tableName);
void print(const std::string& tableName) const;
void print(const std::string& tableName, const std::string& RPN) const;
bool exportTable(const std::string& tableName, const std::string& fileName) const;
std::vector<Row> select(unsigned columnNo, 
    const std::string& value, 
    const std::string& tableName) const;
bool modify(const std::string& tableName, unsigned columnNo, FieldType type);
bool addColumn(const std::string& tableName, const std::string& columnName, FieldType type);
bool updateColumn(const std::string& tableName, unsigned searchColumnNo, const std::string& searchValue, 
    unsigned targetColumnNo, const std::string& targetValue);
bool deleteColumn(const std::string& tableName, unsigned columnNo, const std::string& searchValue);
bool insertColumn(const std::string& tableName, std::vector<std::string> columnValues);
bool createTable(const std::string& name,
                 const std::vector<std::string>& columnNames,
                 const std::vector<FieldType>& columnTypes);
bool dropTable(const std::string& name);
bool deleteFrom(const std::string& tableName,
                unsigned columnNo,
                const std::string& value);
std::vector<Row> selectWhere(const std::string& tableName,
                             unsigned columnNo,
                             const std::string& value) const;
};

#endif