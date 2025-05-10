#pragma once
#ifndef DATA_BASE_HPP

#include "Table.hpp"

class DataBase {
private:
std::vector<Table> tables;

public:
DataBase();
DataBase(std::vector<Table> tables);

const std::vector<Table> getTables() const;

std::vector<std::string> showTables();
std::vector<std::string> describe(const std::string& tableName);
void print(const std::string& tableName) const;
void print(const std::string& tableName, const std::string& RPN) const;
bool exportTable(const std::string& tableName, const std::string& fileName) const;
std::vector<std::vector<std::string>> select(unsigned columnNo, 
    const std::string& value, 
    const std::string& tableName) const;
bool modify(const std::string& tableName, unsigned columnNo, FieldType type);
bool addColumn(const std::string& tableName, const std::string& columnName, FieldType type);
bool updateColumn(const std::string& tableName, unsigned searchColumnNo, const std::string& searchValue, 
    unsigned targetColumnNo, const std::string& targetValue);
bool deleteColumn(const std::string& tableName, unsigned columnNo, const std::string& searchValue);
bool insertColumn(const std::string& tableName, std::vector<std::string> columnValues);
};

#define DATA_BASE_HPP 