#pragma once
#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

class Parser {
public:
    static std::vector<std::string> tokenize(const std::string& input);
    static std::string toLower(const std::string& str);
    static bool isNumber(const std::string& str);
};

#endif