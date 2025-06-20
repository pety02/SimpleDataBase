#include "DataBase.hpp"
#include <iostream>

DataBase::DataBase(const std::string& name) {
    this->setName(name);
    this->setTables(std::vector<Table>());
}

DataBase::DataBase(const std::string& name, std::vector<Table> tables) {
    this->setName(name);
    this->setTables(tables);
}

bool DataBase::setName(const std::string& name) {
    this->name = name;
    return true;
}

bool DataBase::setTables(const std::vector<Table>& tables) {
    this->tables = tables;
    return true;
}

const std::string& DataBase::getName() const {
    return this->name;
}

const std::vector<Table> DataBase::getTables() const {
    return this->tables;
}

std::vector<std::string> DataBase::showTables() {
    std::vector<std::string> result;
    for (const Table& table : tables) {
        result.push_back(table.getName());
    }
    return result;
}

std::vector<std::string> DataBase::describe(const std::string& tableName) {
    std::vector<FieldType> columnTypes;
    std::vector<std::string> columnTypesNames;
    for (const Table& table : tables) {
        if (table.getName() == tableName) {
            columnTypes = table.getColumnTypes();
        }
    }
    for(const FieldType& type : columnTypes) {
        columnTypesNames.push_back(Utils::fieldTypeToString(type));
    }
    return columnTypesNames;
}

void DataBase::print(const std::string& tableName) const {
    for (const Table& table : tables) {
        if (table.getName() == tableName) {
            const auto& rows = table.getRows();
            const auto& colNames = table.getColumnNames();
            for (const auto& name : colNames) {
                std::cout << name << " ";
            }
            std::cout << std::endl;
            for (const Row& row : rows) {
                for (const Field& field : row.getFields()) {
                    std::cout << field.getValue() << " ";
                }
                std::cout << std::endl;
            }
            return;
        }
    }
}

void DataBase::print(const std::string& tableName, const std::string& RPN) const {
    // RPN logic not implemented in this placeholder.
    this->print(tableName); // default to full print
}

bool DataBase::exportTable(const std::string& tableName, const std::string& fileName) const {
    // Placeholder for file export logic
    return true;
}

std::vector<Row> DataBase::select(unsigned columnNo, const std::string& value, const std::string& tableName) const {
    for (const Table& table : tables) {
        if (table.getName() == tableName) {
            std::vector<Row> result;
            for (const Row& row : table.getRows()) {
                if (columnNo < row.getFields().size()) {
                    if (row.getFields()[columnNo].getValue() == value) {
                        result.push_back(row);
                    }
                }
            }
            return result;
        }
    }
    return std::vector<Row>();
}

bool DataBase::modify(const std::string& tableName, unsigned columnNo, FieldType type) {
    for (Table& table : tables) {
        if (table.getName() == tableName) {
            return table.modifyColumnType(columnNo, type);
        }
    }
    return false;
}

bool DataBase::addColumn(const std::string& tableName, const std::string& columnName, FieldType type) {
    for (Table& table : tables) {
        if (table.getName() == tableName) {
            table.addColumn(columnName, type);
            return true;
        }
    }
    return false;
}

bool DataBase::updateColumn(const std::string& tableName, unsigned searchColumnNo, const std::string& searchValue,
                            unsigned targetColumnNo, const std::string& targetValue) {
    for (Table& table : tables) {
        if (table.getName() == tableName) {
            for (Row row : table.getRows()) {
                if (searchColumnNo < row.getFields().size() &&
                    row.getFields()[searchColumnNo].getValue() == searchValue &&
                    targetColumnNo < row.getFields().size()) {
                    FieldType type = row.getFields()[targetColumnNo].getType();
                    Field updatedField(type, targetValue);
                    row.setField(targetColumnNo, updatedField);
                }
            }
            return true;
        }
    }
    return false;
}

bool DataBase::deleteColumn(const std::string& tableName, unsigned columnNo, const std::string& searchValue) {
    for (Table& table : tables) {
        if (table.getName() == tableName) {
            for (Row row : table.getRows()) {
                if (columnNo < row.getFields().size() && row.getFields()[columnNo].getValue() == searchValue) {
                    auto fields = row.getFields();
                    fields.erase(fields.begin() + columnNo);
                    row.setFields(fields);
                }
            }
            return true;
        }
    }
    return false;
}

bool DataBase::insertColumn(const std::string& tableName, std::vector<std::string> columnValues) {
    for (Table& table : tables) {
        if (table.getName() == tableName) {
            if (columnValues.size() != table.getColumnTypes().size()) return false;
            std::vector<Field> newFields;
            for (size_t i = 0; i < columnValues.size(); ++i) {
                Field field(table.getColumnTypes()[i], columnValues[i]);
                newFields.push_back(field);
            }
            table.addRow(Row(newFields));
            return true;
        }
    }
    return false;
}

bool DataBase::createTable(const std::string& name,
                           const std::vector<std::string>& columnNames,
                           const std::vector<FieldType>& columnTypes) {
    for (const auto& table : tables) {
        if (table.getName() == name) {
            return false; // Table with this name does not exist. 
        }
    }

    Table newTable(name, columnNames, columnTypes);
    tables.push_back(newTable);
    return true;
}

bool DataBase::dropTable(const std::string& name) {
    for (auto it = tables.begin(); it != tables.end(); ++it) {
        if (it->getName() == name) {
            tables.erase(it);
            return true;
        }
    }
    return false; // Table is not found.
}

bool DataBase::dropTable(const std::string& name) {
    for (auto it = tables.begin(); it != tables.end(); ++it) {
        if (it->getName() == name) {
            tables.erase(it);
            return true;
        }
    }
    return false; // Table is not found.
}

bool DataBase::deleteFrom(const std::string& tableName,
                          unsigned columnNo,
                          const std::string& value) {
    for (auto& table : tables) {
        if (table.getName() == tableName) {
            std::vector<Row> newRows;
            for (const Row& row : table.getRows()) {
                if (columnNo >= row.getFields().size()) return false;

                if (row.getFields()[columnNo].getValue() != value) {
                    newRows.push_back(row); // Saves only not matching rows.
                }
            }
            return table.setRows(newRows);
        }
    }
    return false;
}

std::vector<Row> DataBase::selectWhere(const std::string& tableName,
                                       unsigned columnNo,
                                       const std::string& value) const {
    for (const auto& table : tables) {
        if (table.getName() == tableName) {
            std::vector<Row> result;
            for (const Row& row : table.getRows()) {
                if (columnNo >= row.getFields().size()) continue;
                if (row.getFields()[columnNo].getValue() == value) {
                    result.push_back(row);
                }
            }
            return result;
        }
    }
    return {}; // Table is not found.
}