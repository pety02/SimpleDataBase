#include "Row.hpp"

Row::Row() {
    this->setFields(std::vector<Field>());
}
Row::Row(const std::vector<Field>& fields) {
    this->setFields(fields);
}
const std::vector<Field>& Row::getFields() const {
    return this->fields;
}
bool Row::setFields(const std::vector<Field>& fields) {
    this->fields = fields;
    return true;
}
bool Row::setField(size_t index, const Field& field) {
    if (index > fields.size()) {   
        return false;
    }

    if (index == fields.size()) {
        fields.push_back(field);
    } else {
        fields.insert(fields.begin() + index, field);
    }

    return true;
}
const std::vector<Field>& Row::getFields() const {
    return this->fields;
}