#include "item.h"

Item::Item(const std::string& name, const std::string& type, int value)
    : name(name), type(type), value(value) {}

std::string Item::getName() const {
    return name;
}

std::string Item::getType() const {
    return type;
}

int Item::getValue() const {
    return value;
}