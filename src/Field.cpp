#include "Field.hpp"
#include "FieldTypeValidator.hpp"

Field::Field() {
    this->setNull();
}

Field::Field(const FieldType& type, const std::string& value) {
    try {
        if(!this->setType(type)) {
            throw std::invalid_argument("Invalid field type: The field type should be STRING, CALENDAR_DATE, FLOAT, INT or NULL.");
        }
        if(!this->setValue(value, type)) {
            throw std::invalid_argument("Invalid field value is dependant of the field type: The field allowed values are different for the different field types.");
        } 
    } catch (const std::invalid_argument& ex) {
        this->setType(FieldType::STRING);
        this->setNull();
    }
}

const FieldType& Field::getType() const {
    return this->type;
}

const std::string Field::getValue() const {
    return this->rawValue;
}

bool Field::isNull() const {
    return this->rawValue == "NULL";
}

bool Field::setType(const FieldType& type) {
    if(type < FieldType::UNKNOWN || FieldType::COUNT < type) {
        return false;
    }  

    this->type = type;
    return true;
}

bool Field::setValue(const std::string& value, const FieldType& type) {
    switch (type) {
        case FieldType::STRING: {
            this->rawValue = value;
            return true;
        }
        case FieldType::CALENDAR_DATE: {
            if (FieldTypeValidator::isValidDate(value)) {
                this->rawValue = value;
                return true;
            }
            this->setNull();
            return false;
        }
        case FieldType::INT: {
            if (FieldTypeValidator::isValidInteger(value)) {
                this->rawValue = value;
                return true;
            }
            this->setNull();
            return false;
        }
        case FieldType::FLOAT: {
            if (FieldTypeValidator::isValidFloat(value)) {
                this->rawValue = value;
                return true;
            }
            this->setNull();
            return false;
        }
        default: {
            this->setNull();
            return false;
        }
    }
}

bool Field::setNull() {
    this->rawValue = "NULL";
    this->type = FieldType::NULL_VALUE;
    return true;
}