#pragma once
#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include "DataBase.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>

class CommandHandler {
private:
    DataBase dataBase;

    void showTables(const std::string& command, std::istringstream& iss);
    void describe(std::istringstream& iss);
    void print(std::istringstream& iss);
    void addColumn(std::istringstream& iss);
    void insertColumn(std::istringstream& iss);
    void creteTable(std::istringstream& iss);
    void dropTable(std::istringstream& iss);
    void deleteFrom(std::istringstream& iss);
    void selectIn(std::istringstream& iss);
public:
    CommandHandler();
    CommandHandler(const DataBase& dataBase);

    bool setDataBase(const DataBase& dataBase);
    const DataBase& getDataBase() const;

    void handleCommand(const std::string& command);
    void loadFile(const std::string& filename);
    void saveFile(const std::string& filename);
};

#endif