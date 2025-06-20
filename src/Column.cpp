#include "Column.hpp"

Column::Column(const std::string& name) {
    this->setName(name);
    this->setValues(std::vector<Field>());
}   
Column::Column(const std::string& name, const std::vector<Field>& values) {
    this->setName(name);
    this->setValues(values);
}
bool Column::setName(const std::string& name) {
    this->name = name;
    return true;
}
bool Column::setValues(const std::vector<Field>& values) {
    if(values.empty()) {
        this->values = values;
        return true;
    }
    FieldType type = values[0].getType();
    for(const Field& field : values) {
        if(field.getType() != type) {
            return false;
        }
    }
    this->values = values;
    return true;
}
const std::string& Column::getName() const {
    return this->name;
}
const std::vector<Field>& Column::getValues() const {
    return this->values;
}