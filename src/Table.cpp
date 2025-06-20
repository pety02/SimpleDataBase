#include "Table.hpp"

Table::Table(std::string name) {
    this->setName(name);
    this->columnNames = std::vector<std::string>();
    this->columnTypes = std::vector<FieldType>();
    this->rows = std::vector<Row>();
}

Table::Table(const std::string& name,
             const std::vector<std::string>& columnNames,
             const std::vector<FieldType>& columnTypes) {
    this->setName(name);
    this->setColumnNames(columnNames);
    this->setColumnTypes(columnTypes);
    this->rows = std::vector<Row>();
}

const std::string& Table::getName() const {
    return this->name;
}

const std::vector<Row>& Table::getRows() const {
    return this->rows;
}

const std::vector<std::string>& Table::getColumnNames() const {
    return this->columnNames;
}

const std::vector<FieldType>& Table::getColumnTypes() const {
    return this->columnTypes;
}

bool Table::setName(const std::string& name) {
    this->name = name;
    return true;
}

bool Table::setColumnNames(const std::vector<std::string>& columnNames) {
    if (!this->rows.empty() && columnNames.size() != this->columnNames.size()) {
        return false; // Changing size is not allowed after rows exist
    }
    this->columnNames = columnNames;
    return true;
}

bool Table::setColumnTypes(const std::vector<FieldType>& columnTypes) {
    if (!this->rows.empty() && columnTypes.size() != this->columnTypes.size()) {
        return false; // Cannot change schema size if data exists
    }
    this->columnTypes = columnTypes;
    return true;
}

bool Table::setRows(const std::vector<Row>& rows) {
    for (const Row& row : rows) {
        if (row.getFields().size() != columnNames.size()) {
            return false;
        }

        const std::vector<Field>& fields = row.getFields();
        for (size_t i = 0; i < fields.size(); ++i) {
            if (fields[i].getType() != columnTypes[i]) {
                return false;
            }
        }
    }

    this->rows = rows;
    return true;
}

void Table::addRow(const Row& row) {
    if (row.getFields().size() != this->columnTypes.size()) {
        return;
    }

    for (size_t i = 0; i < row.getFields().size(); ++i) {
        if (row.getFields()[i].getType() != columnTypes[i]) {
            return;
        }
    }

    this->rows.push_back(row);
}

void Table::addColumn(const std::string& name, FieldType type) {
    this->columnNames.push_back(name);
    this->columnTypes.push_back(type);

    for (size_t i = 0; i < rows.size(); ++i) {
        Field nullField;
        nullField.setType(type);
        nullField.setNull();
        this->rows[i].setField(this->columnNames.size() - 1, nullField);
    }
}

bool Table::modifyColumnType(size_t index, FieldType newType) {
    if (index >= columnTypes.size()) {
        return false;
    }

    for (size_t i = 0; i < rows.size(); ++i) {
        const std::vector<Field>& fields = rows[i].getFields();
        if (index >= fields.size()) {
            return false;
        }

        const std::string& rawValue = fields[index].getValue();
        if (rawValue == "NULL") {
            continue; // NULL is always valid
        }

        Field testField;
        if (!testField.setValue(rawValue, newType)) {
            return false;
        }
    }

    columnTypes[index] = newType;
    for (size_t i = 0; i < rows.size(); ++i) {
        std::vector<Field>& rowFields = const_cast<std::vector<Field>&>(rows[i].getFields());
        Field newField;
        newField.setType(newType);
        newField.setValue(rowFields[index].getValue(), newType);
        rowFields[index] = newField;
    }

    return true;
}

// Construct columns from rows
const std::vector<Column>& Table::getColumns() const {
    std::vector<Column> columns;

    for (size_t i = 0; i < columnNames.size(); ++i) {
        std::vector<Field> columnFields;
        for (const Row& row : rows) {
            const std::vector<Field>& rowFields = row.getFields();
            if (i < rowFields.size()) {
                columnFields.push_back(rowFields[i]);
            }
        }
        Column col(columnNames[i], columnFields);
        columns.push_back(col);
    }

    return columns;
}