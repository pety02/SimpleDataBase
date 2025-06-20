#pragma once
#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include "FieldType.hpp"

class Utils {
public:
    static const std::string& fieldTypeToString(const FieldType& type) {
        switch (type)
        {
        case FieldType::INT:
            return "INTEGER";
        case FieldType::FLOAT:
            return "FLOAT";
        case FieldType::STRING:
            return "STRING";
        case FieldType::CALENDAR_DATE:
            return "CALENDAR_DATE";
        case FieldType::NULL_VALUE:
            return "NULL";
        default:
            return "UNKNOWN FIELD TYPE";
        }
    }
};

#endif