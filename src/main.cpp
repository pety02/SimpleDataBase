#include <iostream>
#include <string>
#include "CommandHandler.hpp"

void printMenu() {
    std::cout << "Welcome to Petya's DataBase console!";
    std::cout << "=========================================";
    std::cout << "                  MENU:                  ";
    std::cout << "=========================================";
    std::cout << std::endl;
    std::cout << "1. show";
    std::cout << "2. describe";
    std::cout << "3. print";
    std::cout << "4. addcol";
    std::cout << "5. insertcol";
    std::cout << "6. create";
    std::cout << "7. drop";
    std::cout << "8. delete";
    std::cout << "9. select";
    std::cout << std::endl;
    std::cout << "Plase, enter valid command from the MENU to be executed...";
}

int main() {
    CommandHandler cmdHandler;

    printMenu();
    std::cout << "Type 'exit' to quit.\n";

    std::string line;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);

        if (line == "exit") {
            break;
        }

        cmdHandler.handleCommand(line);
    }

    std::cout << "Goodbye!\n";
    return 0;
}