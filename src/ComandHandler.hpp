#pragma once
#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include "DataBase.hpp"
#include <string>

class CommandHandler {
private:
    DataBase db;

public:
    CommandHandler();

    void handleCommand(const std::string& command);
    void loadFile(const std::string& filename);
    void saveFile(const std::string& filename);
};

#endif