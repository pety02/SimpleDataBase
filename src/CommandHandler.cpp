#include "CommandHandler.hpp"

void CommandHandler::showTables(const std::string& command, std::istringstream& iss) {
    std::string sub;
    iss >> sub;
    if (sub == "tables") {
        auto tables = this->dataBase.showTables();
        for (const auto& t : tables) {
            std::cout << t << "\n";
        }
    } else {
        std::cout << "Unknown subcommand for 'show'.\n";
    }
}

void CommandHandler::describe(std::istringstream& iss) {
    std::string tableName;
    iss >> tableName;
    auto types = this->dataBase.describe(tableName);
    if (types.empty()) {
        std::cout << "Table not found or has no columns.\n";
    } else {
        for (const auto& type : types) {
            std::vector<std::string> columnTypesNames = dataBase.describe(tableName);
            for(const std::string& typeName : columnTypesNames) {
                std::cout << typeName << " "; 
            }
        }
        std::cout << "\n";
    }
}

void CommandHandler::print(std::istringstream& iss) {
    std::string tableName;
    iss >> tableName;
    this->dataBase.print(tableName);
}

void CommandHandler::addColumn(std::istringstream& iss) {
    std::string tableName, columnName;
    int type;
    iss >> tableName >> columnName >> type;
    if (this->dataBase.addColumn(tableName, columnName, static_cast<FieldType>(type))) {
        std::cout << "Column added.\n";
    } else {
        std::cout << "Failed to add column.\n";
    }
}

void CommandHandler::insertColumn(std::istringstream& iss) {
    std::string tableName;
    iss >> tableName;
    std::vector<std::string> values;
    std::string val;
    while (iss >> val) values.push_back(val);
    if (this->dataBase.insertColumn(tableName, values)) {
        std::cout << "Column inserted.\n";
    } else {
        std::cout << "Failed to insert column.\n";
    }
}

void CommandHandler::creteTable(std::istringstream& iss) {
    std::string sub;
    iss >> sub;
    if (sub == "table") {
        std::string tableName;
        iss >> tableName;
        std::vector<std::string> columnNames;
        std::vector<FieldType> columnTypes;
        std::string columnDef;
        while (iss >> columnDef) {
            size_t colonPos = columnDef.find(':');
            if (colonPos == std::string::npos) {
                std::cout << "Invalid column definition: " << columnDef << "\n";
                return;
            }
            std::string name = columnDef.substr(0, colonPos);
            std::string typeStr = columnDef.substr(colonPos + 1);
            int typeInt = std::stoi(typeStr);
            columnNames.push_back(name);
            columnTypes.push_back(static_cast<FieldType>(typeInt));
        }
        if (this->dataBase.createTable(tableName, columnNames, columnTypes)) {
            std::cout << "Table created.\n";
        } else {
            std::cout << "Failed to create table (maybe name exists).\n";
        }
    }
}

void CommandHandler::dropTable(std::istringstream& iss) {
    std::string sub;
    iss >> sub;
    if (sub == "table") {
        std::string tableName;
        iss >> tableName;
        if (this->dataBase.dropTable(tableName)) {
            std::cout << "Table dropped.\n";
        } else {
            std::cout << "Table not found.\n";
        }
    }
}

void CommandHandler::deleteFrom(std::istringstream& iss) {
    std::string sub;
    iss >> sub;
    if (sub == "from") {
        std::string tableName;
        unsigned columnNo;
        std::string value;
        iss >> tableName >> columnNo >> value;
        if (this->dataBase.deleteFrom(tableName, columnNo, value)) {
            std::cout << "Rows deleted.\n";
        } else {
            std::cout << "Delete failed.\n";
        }
    }
}

void CommandHandler::selectIn(std::istringstream& iss) {
    std::string tableName, dummy, value;
    unsigned columnNo;
    iss >> tableName >> dummy >> columnNo >> dummy >> value; // expecting: select <table> where <colNo> = <value>
    auto rows = this->dataBase.selectWhere(tableName, columnNo, value);
    if (rows.empty()) {
        std::cout << "No matching rows.\n";
    } else {
        for (const Row& row : rows) {
            for (const Field& field : row.getFields()) {
                std::cout << field.getValue() << " ";
            }
            std::cout << "\n";
        }
    }
}

CommandHandler::CommandHandler() : dataBase("default") {}

CommandHandler::CommandHandler(const DataBase& dataBase) : dataBase(dataBase) {}

bool CommandHandler::setDataBase(const DataBase& dataBase) {
    this->dataBase = dataBase;
    return true;
}

const DataBase& CommandHandler::getDataBase() const {
    return this->dataBase;
}

void CommandHandler::handleCommand(const std::string& command) {
    std::istringstream iss(command);
    std::string keyword;
    iss >> keyword;

    if (keyword == "show") {
        this->showTables(command, iss);
    } else if (keyword == "describe") {
        this->describe(iss);
    } else if (keyword == "print") {
        this->print(iss);
    } else if (keyword == "addcol") {
        this->addColumn(iss);
    } else if (keyword == "insertcol") {
        this->insertColumn(iss);
    } else if (keyword == "create") {
        this->creteTable(iss);
    } else if (keyword == "drop") {
        this->dropTable(iss);
    } else if (keyword == "delete") {
        this->deleteFrom(iss);
    } else if (keyword == "select") {
        this->selectIn(iss);
    } else {
        std::cout << "Unknown command.\n";
    }
}

void CommandHandler::saveFile(const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Could not open file for writing: " << filename << "\n";
        return;
    }

    out << "DATABASE " << this->dataBase.getName() << "\n";
    for (const Table& table : this->dataBase.getTables()) {
        out << "TABLE " << table.getName() << "\n";

        // Column names
        const auto& colNames = table.getColumnNames();
        out << "COLUMNS";
        for (const auto& col : colNames) {
            out << " " << col;
        }
        out << "\n";

        // Column types
        const auto& colTypes = table.getColumnTypes();
        out << "TYPES";
        for (const auto& type : colTypes) {
            out << " " << static_cast<int>(type);
        }
        out << "\n";

        // Rows
        for (const Row& row : table.getRows()) {
            out << "ROW";
            for (const Field& field : row.getFields()) {
                out << " " << field.getValue();
            }
            out << "\n";
        }

        out << "ENDTABLE\n";
    }
    out << "ENDDATABASE\n";
    out.close();

    std::cout << "Database saved to " << filename << "\n";
}

void CommandHandler::loadFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Could not open file for reading: " << filename << "\n";
        return;
    }

    std::string line;
    std::string dbName;
    std::vector<Table> tables;

    Table currentTable = Table(this->dataBase.getName());
    bool inTable = false;

    while (std::getline(in, line)) {
        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "DATABASE") {
            iss >> dbName;
        } else if (token == "TABLE") {
            if (inTable) tables.push_back(currentTable);
            std::string tableName;
            iss >> tableName;
            currentTable = Table(tableName);
            inTable = true;
        } else if (token == "COLUMNS") {
            std::string col;
            std::vector<std::string> colNames;
            while (iss >> col) colNames.push_back(col);
            currentTable.setColumnNames(colNames);
        } else if (token == "TYPES") {
            int typeInt;
            std::vector<FieldType> colTypes;
            while (iss >> typeInt) colTypes.push_back(static_cast<FieldType>(typeInt));
            currentTable.setColumnTypes(colTypes);
        } else if (token == "ROW") {
            std::string val;
            std::vector<Field> fields;
            const auto& types = currentTable.getColumnTypes();
            size_t index = 0;
            while (iss >> val && index < types.size()) {
                fields.emplace_back(types[index], val);
                index++;
            }
            currentTable.addRow(Row(fields));
        } else if (token == "ENDTABLE") {
            tables.push_back(currentTable);
            inTable = false;
        }
    }

    in.close();
    this->dataBase.setName(dbName);
    this->dataBase.setTables(tables);

    std::cout << "Database loaded from " << filename << "\n";
}