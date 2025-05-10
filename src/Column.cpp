#include "Column.hpp"

Column::Column(FieldType FieldType) {
    this->type = FieldType;
}   

Column::Column(FieldType FieldType, std::vector<std::string>values) {
    this->type = FieldType;
    this->values = values;
}

const FieldType Column::getFieldType() const {
    return this->type;
}

const std::vector<std::string> Column::getValues() const {
    return this->values;
}