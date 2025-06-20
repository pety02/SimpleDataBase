#pragma once
#ifndef FIELD_TYPE_VALIDATOR_HPP
#define FIELD_TYPE_VALIDATOR_HPP

#include <cctype>  
#include <cstdlib> 
#include <string>

class FieldTypeValidator {
public:
    static bool isValidDate(const std::string& value) {
        if (value.length() != 10) return false;
        if (value[4] != '-' || value[7] != '-') return false;

        for (int i = 0; i < value.length(); ++i) {
            if (i == 4 || i == 7) continue;
            if (!isdigit(value[i])) return false;
        }

        int year = std::atoi(value.substr(0, 4).c_str());
        int month = std::atoi(value.substr(5, 2).c_str());
        int day = std::atoi(value.substr(8, 2).c_str());

        if (month < 1 || month > 12) return false;
        if (day < 1 || day > 31) return false;

        // do not check for a leap year or 30 / 31 days difference between months
        return true;
    }

    static bool isValidInteger(const std::string& value) {
        if (value.empty()) return false;
        size_t i = 0;
        if (value[0] == '-' || value[0] == '+') i = 1;
        for (; i < value.length(); ++i) {
            if (!isdigit(value[i])) return false;
        }
        return true;
    }

    static bool isValidFloat(const std::string& value) {
        bool decimalPointFound = false;
        size_t i = 0;

        if (value.empty()) return false;
        if (value[0] == '-' || value[0] == '+') i = 1;
        if (i == value.length()) return false;

        for (; i < value.length(); ++i) {
            if (value[i] == '.') {
                if (decimalPointFound) return false;
                decimalPointFound = true;
            } else if (!isdigit(value[i])) {
                return false;
            }
        }

        // minimum 1 decimal point
        return decimalPointFound; 
    }
};

#endif